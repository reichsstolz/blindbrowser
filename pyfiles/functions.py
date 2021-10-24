from MainClasses import *
from MinorClasses import *


browser = Browser()


def make_request(url):
    browser.feed(browser._make_request(url))
    req_json = ""
    for i in browser.tree[::-1]:
        req_json += i.toJSON()
    # browser.restore()
    return req_json


