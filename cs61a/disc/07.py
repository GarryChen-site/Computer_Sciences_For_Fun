
class MinList:
    def __init__(self):
        self.items = []
        self.size = 0
    
    def append(self, item):
        self.items.append(item)
        self.size += 1
    
    def pop(self):
        assert self.size > 0, "Can't pop from empty list."
        self.size -= 1
        min_item = min(self.items)
        self.items.remove(min_item)
        return min_item

class Email:
    def __init__(self, msg, sender_name, receiver_name):
        self.msg = msg
        self.sender_name = sender_name
        self.receiver_name = receiver_name
    

class Server:
    def __init__(self):
        self.client = {}
    
    def send(self, email):
        recipient = email.receiver_name
        if recipient not in self.client:
            self.client[recipient].receive(email)
    
    def register_client(self, client, client_name):
        self.client[client_name] = client

class Client:
    def __init__(self, server, name):
        self.inbox = MinList()
        self.server = server
        self.name = name

    def compose(self, msg, recipient_name):
        self.server.send(Email(msg, self.name, recipient_name), self)
    
    def receive(self, email):
        self.inbox.append(email)

class Pet:
    def __init__(self, name, owner):
        self.is_alive = True  # It's alive!!!
        self.name = name
        self.owner = owner

    def eat(self, thing):
        print(self.name + " ate a " + str(thing) + "!")

    def talk(self):
        print(self.name)


class Dog(Pet):
    def talk(self):
        print(self.name + " says woof!")


class Cat(Pet):
    def __init__(self, name, owner, lives=9):
        super().__init__(self, name, owner)
        self.lives = lives
        self.is_alive = True if lives > 0 else False
    
    def talk(self):
        print(self.name + " says meow!")
    
    def lose_life(self):
        if self.is_alive == False:
            print(self.name + " is dead!")
        else:
            self.lives -= 1
            self.is_alive = True if self.lives > 0 else False

class NoisyCat(Cat):

    """__init__ is not necessary, because it is the same as Cat's __init__"""

    def talk(self):
        print(self.name + " says meow!")
        print(self.name + " says meow!")

    def __repr__(self):
        return "NoisyCat ('{}', '{}')".format(self.name, self.owner)