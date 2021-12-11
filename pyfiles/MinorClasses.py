# Copyright 2021 reichsstolz
import re, sys
import threading, json


class Request(threading.Thread):
    def __init__(self, make_request, handle_request, url):
        self.make_request = make_request
        self.handle_request = handle_request
        self.url = url
        super().__init__()

    def run(self):
        self.handle_request(self.make_request(self.url, True))


class CssDeclaration:
    def __init__(self, type, attrs):
        self.attrs = attrs
        self.type = type

    def toJSON(self):
        self.clear_attrs()
        return json.dumps(self, default=lambda o: o.__dict__, sort_keys=True, indent=4)

    def clear_attrs(self):
        allowed_attrs = [
            "height",
            "width",
            "top",
            "bottom",
            "position",
            "left",
            "right",
            "margin",
            "display",
            "margin-bottom",
            "margin-right",
            "margin-left",
            "margin-top",
            "float",
        ]
        for attr in self.attrs:
            if not attr in allowed_attrs:
                self.attrs.pop(attr)

        # add attr delete


class Tag:
    def __init__(self, tag_type, parameters):
        self.tag_type = tag_type
        self.parameters = {}
        for parameter in parameters:
            self.parameters[parameter[0]] = parameter[1]
        self.children = []
        self.data = None

    def add_child(self, kid):
        self.children.append(kid)

    def toJSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, sort_keys=True, indent=4)
