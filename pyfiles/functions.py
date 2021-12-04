from MainClasses import *
from MinorClasses import *


browser = Browser()
alphabet = {
    "a": "100000",
    "b": "110000",
    "c": "100100",
    "d": "100110",
    "e": "100010",
    "f": "110100",
    "g": "110110",
    "h": "110010",
    "i": "010100",
    "j": "010110",
    "k": "101000",
    "l": "111000",
    "m": "101100",
    "n": "101110",
    "o": "101010",
    "p": "111100",
    "q": "111110",
    "r": "111010",
    "s": "011100",
    "t": "011110",
    "u": "101001",
    "v": "111001",
    "w": "010111",
    "x": "101101",
    "y": "101111",
    "z": "101011",
    " ": "000000",
    "konv": "001111",
    "A": "000001",
    ".": "010011",
    ",": "010000",
    "/": "001001",
    "?": "010001",
    "@": "011011",
    "=": "000011",
    "+": "001110",
    ":": "010010",
    ";": "011000"
}
rev_apl = {}
keys = list(alphabet.keys())
vals = list(alphabet.values())
for i in range(len(vals)):
    rev_apl[vals[i]] = keys[i]


def get_request(url):
    browser.feed(browser._make_request(url))
    req_json = {"content": [], "items": 0}
    for i in browser.tree[::-1]:
        req_json["content"].append(i.toJSON())
        req_json["items"] += 1
    # browser.restore()
    return json.dumps(req_json)


def post_request(url, data):
    browser.feed(browser._post_request(url, data))
    req_json = {"content": [], "items": 0}
    for i in browser.tree[::-1]:
        req_json["content"].append(i.toJSON())
        req_json["items"] += 1
    # browser.restore()
    return json.dumps(req_json)


def trans_brail(data):
    initial_str = ""
    digits = False
    values = list(alphabet.values())
    for i in data:
        if i.isdigit():
            if not digits:
                initial_str += alphabet["konv"]
                initial_str += ":"
            if i == "0":
                initial_str += values[9]
            else:
                initial_str += values[int(i) - 1]
            digits = True
        elif i in alphabet.keys():
            if digits and i == " ":
                digits = False
            elif digits:
                digits = False
                initial_str += alphabet["konv"]
                initial_str += ":"
            initial_str += alphabet[i.lower()]
        else:
            initial_str+="000000"
        initial_str += ":"
    return initial_str


def trans_ascii(data):
    data = data.split(":")
    initial_str = ""
    digits = 0
    up = False
    values = list(alphabet.values())
    for i in data:
        if rev_apl.get(i) == "konv":
            digits += 1
            digits %= 2
            continue
        elif digits:
            if rev_apl.get(i) == " ":
                digits = 0
                initial_str += rev_apl.get(i)
                continue
            for k in values:
                if i == k:
                    initial_str += str(values.index(i) + 1)
        elif rev_apl.get(i) == "A":
            up = True
        elif up:
            initial_str += rev_apl.get(i).upper()
            up = False
        else:
            initial_str += rev_apl.get(i)
    return initial_str
