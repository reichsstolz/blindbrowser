

class CssDeclaration:
    def __init__(self, type, attr):
        self.attrs=attr
        self.type=type
        
    def get_relation():
        pass


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
