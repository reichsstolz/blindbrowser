from MainClasses import *
from MinorClasses import *


browser = Browser()


def get_request(url):
    browser.feed(browser._make_request(url))
    req_json = {
    "content":[],
    "items":0
    }
    for i in browser.tree[::-1]:
        req_json["content"].append(i.toJSON())
        req_json["items"]+=1
    # browser.restore()
    return json.dumps(req_json)

def post_request(url, data):
    browser.feed(browser._post_request(url, data))
    req_json = {
    "content":[],
    "items":0
    }
    for i in browser.tree[::-1]:
        req_json["content"].append(i.toJSON())
        req_json["items"]+=1
    # browser.restore()
    return json.dumps(req_json)
