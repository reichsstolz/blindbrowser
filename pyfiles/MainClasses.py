from html.entities import name2codepoint
from html.parser import HTMLParser
from MinorClasses import *
import re, os, hashlib, copy
from urllib import request, parse


class Browser(HTMLParser):
    def __init__(self, js=False, css=False):
        self.current_url = None
        self.css_list = []
        self.js_files = []
        super().__init__()
        self.parent_tag = []
        self.tree = []
        self.js = js
        self.css = css

    def _make_request(self, url, parsing=False):
        if url.startswith("/") and parsing:
            url = self.current_url + url
        elif not url.startswith("http") and parsing:
            url = self.current_url + "/" + url
        elif not parsing:
            self.current_url = re.search(
                r"https:\/\/[a-zA-Z0-9.-]{1,}|http:\/\/[a-zA-Z0-9.-]{1,}", url
            ).group(0)

        resp = request.urlopen(url)
        text = resp.read()
        return text.decode("utf-8")

    def _post_request(self, url, data):
        data = json.loads(data)
        data = parse.urlencode(data).encode()
        req = request.Request(url, data)
        resp = request.urlopen(req)
        return resp.read().decode("utf-8")

    def _handle_css(self, parsed):

        parsed = re.findall(r"([a-zA-Z\.#,_\-:]{1,})\s*\{([^}]{1,})\}", parsed)
        css_tree = []
        temp_attrs = {}
        for tags, attrs in parsed:
            for key, val in re.findall(r"([a-z\-]{1,}):([^;]{1,});?", attrs):
                temp_attrs[key] = val
            if temp_attrs.keys():

                if not "," in tags:
                    for types in tags.split(" "):
                        if types:
                            # print("TEMP", types,  temp_attrs)
                            self.css_list.append(
                                CssDeclaration(types, copy.copy(temp_attrs))
                            )
                else:
                    for types in tags.split(","):
                        if types:
                            self.css_list.append(
                                CssDeclaration(types, copy.copy(temp_attrs))
                            )

            temp_attrs.clear()

    def _handle_js(self, js_text):
        if not os.path.exists("temp_js"):
            os.mkdir("temp_js")
        hash_js = hashlib.sha1(js_text.encode()).hexdigest()
        file = open("temp_js/" + hash_js + ".js", "w")
        file.write(js_text)
        file.close()
        self.js_files.append(hash_js)

        """PARSER"""

    def restore(self):
        self.css_list = []
        self.js_files = []
        self.tree = None

    def handle_starttag(self, tag, attrs):

        # print("Start tag:", tag)
        new_tag = Tag(tag, attrs)
        if self.parent_tag:
            self.parent_tag[-1].add_child(new_tag.tag_type)
        if (
            tag == "link"
            and new_tag.parameters.get("rel") == "stylesheet"
            and new_tag.parameters.get("href")
            and self.css
        ):
            pass
            newreq = Request(
                self._make_request, self._handle_css, new_tag.parameters.get("href")
            )
            newreq.start()

        elif tag == "script" and new_tag.parameters.get("src") and self.js:
            newreq = Request(
                self._make_request, self._handle_js, new_tag.parameters.get("src")
            )
            newreq.start()
            self.parent_tag.append(new_tag)
            # print("found src  ", new_tag.parameters.get("src"))
            # self._handle_js(self._make_request(new_tag.parameters.get("src"), True))

        else:
            self.parent_tag.append(new_tag)

    def handle_endtag(self, tag):
        for i in range(len(self.parent_tag) - 1, -1, -1):
            if self.parent_tag[i].tag_type == tag:
                for a in range(i, len(self.parent_tag)):
                    last_tag = self.parent_tag.pop()
                    self.tree.append(last_tag)
                    # print(last_tag.tag_type)
                    if last_tag.tag_type == "html":
                        print("FOUND LAST TAG")

                break

        # print(tag.tag_type)

    def handle_data(self, data):

        if self.parent_tag:
            if self.parent_tag[-1].tag_type == "script" and self.js:
                self._handle_js(data)
            elif self.parent_tag[-1].tag_type == "style" and self.css:
                self._handle_css(data)
            else:
                self.parent_tag[-1].data = data
        # print("Data     :", data)

    def handle_comment(self, data):
        pass

    # print("Comment  :", data)

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
