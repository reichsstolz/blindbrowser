from html.entities import name2codepoint
from html.parser import HTMLParser
from MinorClasses import *
import aiohttp
import asyncio
import re

class Browser:
    def __init__(self):
        self.session = aiohttp.ClientSession()
        self.loop = asyncio.get_event_loop()
        self.current_url=None

    def dead(self):
        self.loop.run_until_complete(self.session.close())

    def get_request(self, url, parsing=False):
        return self.loop.run_until_complete(self._make_request(url, parsing))

    def handle_css(self, url):
        return self.loop.run_until_complete(self._handle_css(url))


    async def _make_request(self, url, parsing):
        if url.startswith("/") and parsing:
            url = self.current_url + url
        elif not url.startswith("http") and parsing:
            url= self.current_url+"/"+url
        elif not parsing:
            self.current_url = re.search(r"https:\/\/[a-zA-Z0-9.-]{1,}|http:\/\/[a-zA-Z0-9.-]{1,}", url).group(0)
        resp = await self.session.get(url)
        print(resp.status)
        return await resp.text()

    async def _post_request(self, url):
        pass

    async def _handle_css(self, parsed):
        parsed = re.findall(r"([a-zA-Z\.#,_\-:]{1,})\s*\{([^}]{1,})\}", parsed)
        css_tree=[]
        temp_attrs={}
        for tags, attrs in parsed:
            for key, val in re.findall(r"([a-z\-]{1,}):([^;]{1,});?",attrs):
                 temp_attrs[key]=val
            for types in tags.split(","):
                css_tree.append(CssDeclaration(types,temp_attrs))
                temp_attrs.clear()
        return css_tree

    async def handle_js(self, url):
        pass


class Parser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.parent_tag = []
        self.tree = None
        self.css_urls=[]
        self.js_urls=[]

    def handle_starttag(self, tag, attrs):
        # print("Start tag:", tag)
        new_tag = Tag(tag, attrs)
        if tag=="link" and new_tag.parameters.get("rel")=="stylesheet" and new_tag.parameters.get("href"):
            self.css_urls.append(new_tag.parameters.get("href"))

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


"""
class User:
    def __init__(self):
        pass
"""
