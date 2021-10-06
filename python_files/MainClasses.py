from html.entities import name2codepoint
from html.parser import HTMLParser
from MinorClasses import *
import aiohttp
import asyncio
import re
import os
import hashlib
import requests as r


class Browser(HTMLParser):
    def __init__(self):
        self.session = aiohttp.ClientSession()
        self.loop = asyncio.get_event_loop()
        self.current_url = None
        self.css_list = []
        self.js_files = []
        super().__init__()
        self.parent_tag = []
        self.tree = None

    def dead(self):
        self.loop.run_until_complete(self.session.close())

    def get_request(self, url, parsing=False):
        return self.loop.run_until_complete(self._make_request(url, parsing))

    def handle_css(self, parsed):
        return self.loop.run_until_complete(self._handle_css(parsed))

    def handle_js(self, parsed):
        return self.loop.run_until_complete(self._handle_js(parsed))

    async def _make_request(self, url, parsing):
        if url.startswith("/") and parsing:
            url = self.current_url + url
        elif not url.startswith("http") and parsing:
            url = self.current_url + "/" + url
        elif not parsing:
            self.current_url = re.search(
                r"https:\/\/[a-zA-Z0-9.-]{1,}|http:\/\/[a-zA-Z0-9.-]{1,}", url
            ).group(0)
        resp = await self.session.get(url)
        print(resp.status)
        try:
            return await resp.text()
        except Exception as e:
            print("\nREQUEST FAILED {}\n".format(url))

            return r.get(url).text  # hmm, what's the problem

    async def _post_request(self, url):
        pass

    async def _handle_css(self, parsed):
        parsed = re.findall(r"([a-zA-Z\.#,_\-:]{1,})\s*\{([^}]{1,})\}", parsed)
        css_tree = []
        temp_attrs = {}
        for tags, attrs in parsed:
            for key, val in re.findall(r"([a-z\-]{1,}):([^;]{1,});?", attrs):
                temp_attrs[key] = val
            if not "," in tags:
                for types in tags.split(" "):
                    if types:
                        css_tree.append(CssDeclaration(types, temp_attrs))
            else:
                for types in tags.split(","):
                    if types:
                        css_tree.append(CssDeclaration(types, temp_attrs))
            temp_attrs.clear()
        return css_tree

    async def _handle_js(self, js_text):
        if not os.path.exists("temp_js"):
            os.mkdir("temp_js")
        hash_js = hashlib.sha1(js_text.encode()).hexdigest()
        file = open("temp_js/" + hash_js + ".js", "w")
        file.write(js_text)
        file.close()
        self.js_files.append(hash_js)

        """PARSER"""

    def feed_restore(self, response):
        self.feed(response)
        self.restore()
        self.tree = None

    def restore(self):
        self.css_list = []
        self.js_files = []

    def handle_starttag(self, tag, attrs):
        # print("Start tag:", tag)
        new_tag = Tag(tag, attrs)
        if (
            tag == "link"
            and new_tag.parameters.get("rel") == "stylesheet"
            and new_tag.parameters.get("href")
        ):
            self.css_list += self.handle_css(
                self.get_request(new_tag.parameters.get("href"), True)
            )

        if tag == "script" and new_tag.parameters.get("src"):
            self._handle_js(self.get_request(new_tag.parameters.get("src"), True))

        if self.parent_tag:
            self.parent_tag[-1].add_children(new_tag)
        self.parent_tag.append(new_tag)
        #    print("     attr:", attr)

    def handle_endtag(self, tag):
        # print("End tag  :", tag)
        tag = self.parent_tag.pop()
        if tag.tag_type == "html":
            self.tree = tag

    def handle_data(self, data):

        if self.parent_tag:
            if self.parent_tag[-1].tag_type == "script":
                self.handle_js(data)
            elif self.parent_tag[-1].tag_type == "style":
                self.css_list += self.handle_css(data)
            else:
                self.parent_tag[-1].data = data
        # print("Data     :", data)

    def handle_comment(self, data):
        print("Comment  :", data)

    def handle_entityref(self, name):
        c = chr(name2codepoint[name])
        print("Named ent:", c)

    def handle_charref(self, name):
        if name.startswith("x"):
            c = chr(int(name[1:], 16))
        else:
            c = chr(int(name))
        print("Num ent  :", c)

    def handle_decl(self, data):
        print("Decl     :", data)


class Storage:
    def __init__(self):
        self.js_files = []
        self.css_dictionary = []
        self.html_tree = None

    def add_js_files(self, js_files):
        self.js_files += js_files

    def add_css(self, css_list):
        self.css_dictionary += css_list

    def add_html(self, tree):
        self.html_tree = tree

    def compare_css_html(self):
        pass

    def restore(self):  # delete all files
        for file in self.js_files:
            os.remove("temp_js/" + file + ".js")
        self.js_files = []
        self.css_dictionary = []
        self.html_tree = None
