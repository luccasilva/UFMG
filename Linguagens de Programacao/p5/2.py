class Node:
   def __init__ ( self ) :
      self . next = 0
      self . element = ''

class Stack:
   def __init__ ( self ) :
      self . top = None

   def add ( self,x ) :
      new_node = Node()
      new_node.element = x
      new_node.next = self.top
      self . top = new_node

   def remove ( self ) :
      node = self.top
      self.top = node.next
      element = node.element
      del node
      return element

   def isNotEmpty ( self ) :
      return self.top != None