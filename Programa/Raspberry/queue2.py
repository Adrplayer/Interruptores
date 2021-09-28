# queue.py

class Queue:
    def __init__(self, limit=None):
        """ Creates a white queue """
        # the empty queue it's made of a white array
        self.limit = limit
        self.items = []

    def push(self, x):
        """ Add the element 'x' in the last place """
        if self.limit is None:
            self.items.append(x)
        else:
            if len(self.items) >= self.limit:
                self.items.append(x)
                self.items.pop(0)
            else:
                self.items.append(x)

    def pop(self):
        """ Delete the first element and return it """
        try:
            return self.items.pop(0)
        except:
            raise ValueError("The Queue is empty")

    def len(self):
        """ Return the len of the Queue"""
        return len(self.items)

    def get_queue(self):
        """ Return a snapshot of the Queue"""
        tmp = self.items
        return tmp

    def is_empty(self):
        """ Return True if the queue is empty, False instead"""
        return self.items == []
