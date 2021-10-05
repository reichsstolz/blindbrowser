import asyncio
import re
class CssDeclaration:
    def __init__(self, type, attr):
        self.attrs = attr
        self.id=None
        self.class=None
        self.tag=None
        if type[0]=="#":
            self.id=type

        elif re.match(r"[a-zA-Z_\-]{0,}\.[a-zA-Z_\-]{1,}", type):
            self.tag, self.class=type.split(".")

        elif re.match("[a-zA-Z_\-]{1,}", type):
            self.tag = type

        if !self.tag:
            self.tag = None
        # add attr delete
        
    def get_relation():
        return (self.tag, self.class, self.id)


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

async def merge_css(css, html):
    pass
