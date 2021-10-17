from MainClasses import *
from MinorClasses import *

global browser
browser = Browser()


def make_request(url):
    return browser._make_request(url)
    #browser.feed(browser._make_request(url))
