import asyncio
import re, sys


class CssDeclaration:
    def __init__(self, type, attr):
        self.attrs = attr
        self.id = None
        self._class = None
        self.tag = None
        try:
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
        except Exception as e:
            print(e)
            print("\n\n A OCCASION\n\n")
            print(type, attr)
            sys.exit()
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
