from MainClasses import *
from MinorClasses import *


browser = Browser()


def get_request(url):
    browser.feed(browser._make_request(url))
    req_json = ""
    for i in browser.tree[::-1]:
        req_json += i.toJSON()
    # browser.restore()
    return req_json

def post_request(url, data):
    browser.feed(browser._post_request(url, data))
    req_json = ""
    for i in browser.tree[::-1]:
        req_json += i.toJSON()
    # browser.restore()
    return req_json
