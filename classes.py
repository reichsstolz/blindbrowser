import asyncio
import aiohttp
from PyQt5.QtWidgets import QWidget, QDesktopWidget
from html.parser import HTMLParser
from html.entities import name2codepoint

class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):
        self.resize(300, 500)
        self.setWindowTitle("BlindBrowser")
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

    async def post_request(self, url):
        pass



class Parser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print("Start tag:", tag)
        for attr in attrs:
            print("     attr:", attr)

    def handle_endtag(self, tag):
        print("End tag  :", tag)

    def handle_data(self, data):
        print("Data     :", data)

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


class Tag:
    def __init__(self, tag_type, parameters):
        self.tag_type=tag_type




"""
class User:
    def __init__(self):
        pass
"""
