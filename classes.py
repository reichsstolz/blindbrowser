import asyncio
import aiohttp
from PyQt5.QtWidgets import QWidget, QDesktopWidget, QPushButton, QGridLayout, QLabel
from PyQt5.QtCore import Qt
from html.parser import HTMLParser
from html.entities import name2codepoint
import re

class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):
        self.resize(300, 500)
        self.setWindowTitle("BlindBrowser")
        self.label = QLabel("BlindBrowser", self)
        self.label.setAlignment(Qt.AlignCenter)
        self.label.resize(290, 450)
        self.box = QGridLayout()
        buttons_settings=[ "<-", "Up", "->",
                           ".", "Down", "."]
        place_settings=[(i,j) for i in range(2)  for j in range(3)]

        for button, pos  in zip(buttons_settings, place_settings):
            self.box.addWidget(QPushButton(button), *pos)

        self.box.setAlignment(Qt.AlignBottom)
        self.setLayout(self.box)
        self.show()


class Browser:
    def __init__(self):
        self.session = aiohttp.ClientSession()
        self.loop = asyncio.get_event_loop()

    def dead (self):
        self.loop.run_until_complete(self.session.close())

    async def _make_request(self, url):
            resp = await self.session.get(url)
            print(resp.status)
            #print(resp.text())
            return await resp.text()

    def make_request(self, url):
        return self.loop.run_until_complete(self._make_request(url))

    async def _post_request(self, url):
        pass

class Tag:
    def __init__(self, tag_type, parameters):
        self.tag_type=tag_type
        self.parameters={}
        for parameter in parameters:
            self.parameters[parameter[0]]=parameter[1]
        self.children = []
        self.data=None

    def add_children(self, kid):
        self.children.append(kid)

class Parser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.parent_tag = []
        self.tree = None

    def handle_starttag(self, tag, attrs):
        #print("Start tag:", tag)
        new_tag = Tag(tag, attrs)
        if new_tag.parameters.get("href"):
            if new_tag["href"].endwith(".ccs"):
                pass  # write css handler
        if self.parent_tag:
            self.parent_tag[-1].add_children(new_tag)
        self.parent_tag.append(new_tag)
        #    print("     attr:", attr)

    def handle_endtag(self, tag):
        #print("End tag  :", tag)
        tag = self.parent_tag.pop()
        if tag.tag_type == "html":
            self.tree = tag

    def handle_data(self, data):
        self.parent_tag[-1].data = data
        #print("Data     :", data)

    def handle_comment(self, data):
        print("Comment  :", data)

    def handle_entityref(self, name):
        c = chr(name2codepoint[name])
        print("Named ent:", c)

    def handle_charref(self, name):
        if name.startswith('x'):
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
