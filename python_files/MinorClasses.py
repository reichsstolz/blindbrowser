import re, sys
import threading

class Request(threading.Thread):
        def __init__(self, make_request, handle_request, url):
            self.make_request=make_request
            self.handle_request=handle_request
            self.url=url
            super().__init__()
        def run (self):
            self.handle_request(self.make_request(self.url, True))


class CssDeclaration:
    def __init__(self, type, attr):
        self.attrs = attr
        self.id = None
        self._class = None
        self.tag = None

        if type[0] == "#":
            self.id = type

        if re.match(r"[a-zA-Z_\-]{0,}\.[a-zA-Z_\-]{1,}", type):
            if type.count(".") > 1:
                self._class = type
            else:
                self.tag, self._class = type.split(".")

        elif re.match("[a-zA-Z_\-]{1,}", type):
            self.tag = type
        if not self.tag:
            self.tag = None


        # add attr delete
    def get_relation():
        return (self.tag, self._class, self.id)


class Tag:
    def __init__(self, tag_type, parameters):
        self.tag_type = tag_type
        self.parameters = {}
        for parameter in parameters:
            self.parameters[parameter[0]] = parameter[1]
        self.children = []
        self.data = None

    def add_children(self, kid):
        self.children.append(kid)
