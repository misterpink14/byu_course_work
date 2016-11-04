__author__ = 'Ben Thompson'
__email__ = 'misterpink14@gmail.com'



class UnrolledLinkedList(object):
    """ This is the container class for your unrolled linked list """

    class Node(object):
        """ This is the node object you should use within your unrolled linked
            list
        """

        def __init__(self, data = [], next_node = None):
            self.data = data
            self.next_node = next_node

    def __init__(self, max_node_capacity=16):
        """  The constructor for the list.

        The default max node capacity is 16, but this value should be
        overridable.

        """
        self.head = None
        self.tail = None
        self.max_node_capacity = max_node_capacity
        self.length = 0

    def __add__(self, other):
        """ Appends two Unrolled Linked Lists end-to-end using `+`

        Usage: `
            list_one = UnrolledLinkedList()
            list_two = UnrolledLinkedList()
            new_list = list_one + list_two
        `

        Args:
            other: Another Unrolled Linked List object. The new ULL should have
                the same max capacity as the current ULL.

        Returns:
            A new unrolled linked list.

        Raises:
            TypeError: If the passed in `other` parameter is not an unrolled
                linked list, raise this error. Users should not be able to
                append anything to an unrolled linked list besides another
                unrolled linked list.
        """
        if not type(other) == type(self):
            raise TypeError()

        new_list = self._copy()

        for i in xrange(len(other)):
            new_list.append(other[i])
        return new_list

    def __mul__(self, count):
        """ Repeats (multiplies) the list a given number of times

        Usage: `my_list *= 5` should return a list of itself repeated 5x

        Args:
            count: An integer indicating the number of times the list should
                be repeated.

        Returns:
            The new data structure multiplied however many times indicated

        Raises:
            TypeError: If count is not an int

        """
        if not type(count) == type(1):
            raise TypeError()
        new_list = self._copy()
        count -= 1
        while count != 0:
            count -= 1
            for i in xrange(self.length):
                new_list.append(self[i])
        return new_list


    def __getitem__(self, index):
        """ Access the element at the given index.

        The indexes of an unrolled linked list refers to the total collection
        of the list. i.e. in {[1, 2, 3], [5, 4, 1]}, index @ 1 refers to the
        value 2. Index @ 4 refers to the value 4, even though it is in another
        node.

        This function should support negative indices, which are natural to
        Python. For example, getting at index -1 should return the last
        element, index -2 should be the second-to-last element and so on.

        Usage: `my_list[4]`

        BONUS: Allow this to work with slices. The resulting structure should
        be a new balanced unrolled linked list.
        For example,
        my_list = {[1, 2, 6], [9, 6, 1], [0, 8, 1], [8, 2, 6]}
        then my_list[4:10] should be {[6, 1, 0], [8, 1, 8, 2, 6]}

        Args:
            index: An int value indicating an index in the list.

        Returns:
            The object held at the given `index`.

        Raises:
            TypeError: If index is not an `int` object.
            IndexError: If the index is out of bounds.

        """
        index = self._validateIndex(index)
        index, n = self._find(index, self.head)
        return n.data[index]


    def __len__(self):
        """Return the total number of items in the list

        Usage: `len(my_list)`

        Returns:
            An int object indicating the *total* number of items in the list,
            NOT the number of nodes.
        """
        return self.length

    def __setitem__(self, index, value):
        """ Sets the item at the given index to a new value

        Usage: `my_list[5] = "my new value"`

        BONUS: Allow this to work with slices. You should *only* be able to
        assign another unrolled linked list. Upon doing so, you should
        rebalance the list. For example, if your node max capacity is 5, and
        your list is:
        my_list = {[1, 2, 6], [9, 6, 1], [0, 8, 1], [8, 2, 6]}
        and you have another list with a different max capacity:
        other_list = {[3, 6], [8, 4]},
        and you use `my_list[0:2] = other_list` the result should be
        {[3, 6, 8, 4, 6], [9, 6, 1], [0, 8, 1], [8, 2, 6]}
        which is acceptable since the max capacity is 5. Node 0 did not go over

        Args:
            index: The index of the list which should be modified.
            value: The new value for the list at the given index.

        Returns:
            none - this is a void function and should mutate the data structure
                in-place.

        Raises:
            TypeError: If index is not an `int` object.
            IndexError: If the index is out of bounds.
        """
        index = self._validateIndex(index)
        index, n = self._find(index, self.head)
        n.data[index] = value

    def __delitem__(self, index):
        """ Deletes an item using the built-in `del` keyword

        This function should support negative indices, which are natural to
        Python. For example, deleting at index -1 should delete the last
        element, index -2 should be the second-to-last element and so on.

        RULES FOR DELETING (paraphrased from Wikipedia):
        To remove an element, we simply find the node it is in and delete it
        from the elements array, decrementing numElements. If this reduces the
        node to less than half-full, then we move elements from the next node
        to fill it back up above half. If this leaves the next node less than
        half full, then we move all its remaining elements into the current
        node, then bypass and delete it.

        BONUS: Allow this to delete using slices as well as indices
        (http://stackoverflow.com/questions/12986410/how-to-implement-delitem-to-handle-all-possible-slice-scenarios)

        Usage: `del my_list[4]`

        Args:
            index: An `int` value indicating the index of the item you are
                deleting.

        Returns:
            none - this is a void function that should mutate the data
                structure in-place, not return a new data structure.

        Raises:
            TypeError: If index is not an `int` object.
            IndexError: If the index is out of bounds.
        """
        index = self._validateIndex(index)
        index, n = self._find(index, self.head)
        del n.data[index]
        if len(n.data) < self.max_node_capacity/2:
            self._rebalance(n)
        self.length -= 1

    def __iter__(self):
        """ Returns an iterable to allow one to iterate the list.

        This dunder function allows you to use this data structure in a loop.

        Usage: `for value in my_list:`

        Returns:
            An iterator that points to each value in the list using the `yield`
                statement.
        """
        n = self.head

        isMore = True
        while isMore:
            for v in n.data:
                yield v
            if not n.next_node:
                isMore = False
            else:
                n = n.next_node

    def __contains__(self, item):
        """ Returns True/False whether the list contains the given item

        Usage: `5 in my_list`

        Args:
            item: The object for which containment is being checked for.

        Returns:
            True: if `item` is found somewhere in the list
            False: if `item` is not found anywhere in the list
        """
        n = self.head

        isFound = False
        isMore = True
        while isMore:
            for v in n.data:
                if v == item:
                    return True
            if not n.next_node:
                isMore = False
            else:
                n = n.next_node
        return False


    def append(self, data):
        """ Add a new object to the end of the list.

        This adds a new object, increasing the overall size of the list by 1.

        RULES FOR APPENDING (paraphrased from Wikipedia):
        To insert a new element, we simply find the node the element should be
        in and insert the element into the elements array, incrementing
        the size of the list. If the array is already full, we first insert a
        new node either preceding or following the current one and move half of
        the elements in the current node into it.

        For appending you should always create a new node at the end of the
        list.

        Usage: `my_list.append(4)`

        Args:
            data: The new object to be added to the list

        Returns:
            nothing

        """
        if not self.head:
            n = UnrolledLinkedList.Node([])
            self.head = n
            self.tail = n
        if (len(self.tail.data) == self.max_node_capacity):
            self._splitLastNode()
        self.tail.data.append(data)
        self.length += 1


    def __reversed__(self):
        """ Works just like __iter__, but starts from the back.

        Usage: `for i in reversed(my_list)`

        Returns:
            An iterator starting from the back of the list
        """
        for i in reversed(range(self.length)):
            index, n = self._find(i, self.head)
            yield n.data[index]


    def __str__(self):
        """ Returns a string representation of the list.

        The format for representing an unrolled linked list will be as follows:
            - curly braces indicates an unrolled linked list
            - square brackets indicates a node
            - all values are separated by a comma and a space
        For example:
        {[1, 2, 3], [0, 9, 8], [2, 4, 6]}
        This list has three nodes and each node as three int objects in it.

        Usage: `str(my_list)`

        Returns:
            A string representation of the list.
        """
        if not self.head or not self.head.data:
            return "{}"
        n = self.head
        out = "{" + str(n.data)
        while n.next_node != None:
            n = n.next_node
            out += ", " + str(n.data)
        out += "}"
        return out



    # Helper functions

    def _rebalance(self, n):
        """
        Move elements from the next node to fill it back up above half. 
        If this leaves the next node less than half full, then we move 
        all its remaining elements into the current node, then bypass 
        and delete it.
        """
        if n.next_node:
            n_next = n.next_node
            needed = self.max_node_capacity/2 - len(n.data)
            for i in xrange(needed):
                if len(n_next.data) == i:
                    break
                n.data.append(n_next.data[i])
            for i in xrange(needed):
                if len(n_next.data) == 0:
                    break
                del n_next.data[0]
            if len(n_next.data) < self.max_node_capacity/2:
                for i in xrange(len(n_next.data)):
                    n.data.append(n_next.data[i])
                n.next_node = n_next.next_node


    def _copy(self):
        new_list = UnrolledLinkedList(self.max_node_capacity)
        isMore = True
        n = self.head
        while isMore:
            for v in n.data:
                new_list.append(v)
            if not n.next_node:
                isMore = False
            else:
                n = n.next_node
        return new_list


    def _validateIndex(self, index):
        if not type(1) == type(index):
            raise TypeError()
        if index < 0:
            index += self.length
        return index


    def _find (self, index, n):
        while not len(n.data) > index:
            if n.next_node == None:
                raise IndexError()
            index -= len(n.data)
            n = n.next_node
        return index, n


    def _splitLastNode(self):
        # get the last Node
        curr_node = self.tail
        data = curr_node.data

        # Split the array in half
        half = len(data)/2
        if len(data) % 2 == 1:
            half += 1
        list1 = data[:half]
        list2 = data[half:]

        # Apply changes to curr node and create a Node
        curr_node.data = list1
        new_node = UnrolledLinkedList.Node(list2)
        curr_node.next_node = new_node
        self.tail = new_node # point tail to the end
