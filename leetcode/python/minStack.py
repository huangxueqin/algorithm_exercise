class MinStack:
    # initialize your data structure here.
    def __init__(self):
       self.minE = 0
       self.array = []

    # @param x, an integer
    # @return nothing
    def push(self, x):
        self.array.append(x)
        if len(self.array) == 1:
            self.minE = self.array[0]
        else:
            if self.minE > x:
                self.minE = x

    # @return nothing
    def pop(self):
        if len(self.array) > 0:
            top = self.top()
            self.array.pop()
            if top == self.minE:
                self.minE = self.top()
                for x in self.array:
                    if x < self.minE:
                        self.minE = x
        else:
            return None


    # @return an integer
    def top(self):
        if len(self.array) > 0:
            return self.array[-1]
        else:
            return None

    # @return an integer
    def getMin(self):
        if len(self.array) > 0:
            return self.minE
        else:
            return None
