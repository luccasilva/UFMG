class Node:
   def __init__(self):
      self.next = 0
      self.element = ""
      self.previous = 0

class Queue:
   def __init__(self):
      self.fisrt = None
      self.last = None

   def isNotEmpty(self):
      if self.fisrt != None:
         return True
      return False

   def add(self,x):
      new_node = Node()
      new_node.element = x
      if self.fisrt == None:
         self.fisrt = new_node
         self.last = new_node
      else:
         new_node.previous = self.last
         self.last.next = new_node
         self.last = new_node

   def remove(self):
      node = self.first
      if self.first == self.last :
         self.last = None
      self.first = node.next
      return node.last

   def isNotEmpty ( self ) :
      return self.first != None

   def getSmaller(self):
      if self.first == None:
         return None

      smaller = self.first.element
      if self.first.next != None:
         node = self.first.next
      else:
         node = 0
      while node != 0:
         if node.element < smaller:
            smaller = node.element
         node = node.next
      return smaller