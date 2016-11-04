__author__ = 'Ben Thompson'
__email__ = 'misterpink14@gmail.com'

import unittest
from unrolled_linked_list import UnrolledLinkedList

'''
> Impliment your tests here

To run your tests, just run `python tests.py`
'''


# class ExampleTest(unittest.TestCase):
# 	""" Demonstrates how the unittest framework works """

# 	def test_example(self):
# 		new_list = UnrolledLinkedList()
# 		self.assertIsNotNone(new_list)



class UnrolledLinkedListTest(unittest.TestCase):
	""" Demonstrates how the unittest framework works """

	def setUp(self):
		self.new_list = UnrolledLinkedList()


	def test_init(self):
		self.assertIsNotNone(self.new_list)


	def test_max_node_capacity(self):
		self.new_list = UnrolledLinkedList(4)
		for i in xrange(5):
			self.new_list.append(i)
		self.assertEquals(
			str(self.new_list),
			"{[0, 1], [2, 3, 4]}"
		)


	def test_empty_str(self):
		self.assertEquals(str(self.new_list), "{}")


	def test_small_str(self):
		self.new_list.append(1)
		self.assertEquals(str(self.new_list), "{[1]}")


	def test_large_str(self):
		self.new_list.append(1)
		self.new_list.append(2)
		self.new_list.append(3)
		self.new_list.append(4)
		self.new_list.append(5)
		self.new_list.append(6)
		self.new_list.append(7)
		self.new_list.append(8)
		self.new_list.append(9)
		self.new_list.append(10)
		self.new_list.append(11)
		self.new_list.append(12)
		self.new_list.append(13)
		self.new_list.append(14)
		self.new_list.append(15)
		self.new_list.append(16)
		self.new_list.append(17)
		self.new_list.append(18)
		self.assertEquals(
			str(self.new_list), 
			"{[1, 2, 3, 4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15, 16, 17, 18]}"
		)


	def test_append(self):
		self.new_list.append(1)
		self.new_list.append(2)
		self.assertEquals(self.new_list.length, 2)


	def test_len_base(self):
		self.assertEquals(0, len(self.new_list))

	
	def test_len_append(self):
		self.new_list.append(1)
		self.new_list.append(3)
		self.new_list.append(4)
		self.assertEquals(3, len(self.new_list))

	
	def test_len_del(self):
		self.new_list.append(1)
		self.new_list.append(3)
		self.new_list.append(4)
		del self.new_list[0]
		self.assertEquals(2, len(self.new_list))


	def test_invalid_add(self):
		self.assertRaises(TypeError, lambda: self.new_list + 0)


	# this test applies to getitem, setitem, delitem (all throw errors in a shared helper function)
	def test_typeerror_getitem(self): 
		self.new_list.append(1)
		self.assertRaises(TypeError, lambda: self.new_list["9"])


	# this test applies to getitem, setitem, delitem (all throw errors in a shared helper function)
	def test_indexerror_getitem(self): 
		self.new_list.append(1)
		self.assertRaises(IndexError, lambda: self.new_list[9])


	def test_getitem(self):
		for i in xrange(18):
			self.new_list.append(i)
		self.assertTrue(
			(self.new_list[0] == 0) and
			(self.new_list[16] == 16) and
			(self.new_list[17] == 17)
		)


	def test_setitem(self):
		for i in xrange(4):
			self.new_list.append(i)
		self.new_list[0] = 100
		self.assertEquals(str(self.new_list), "{[100, 1, 2, 3]}")


	def test_delitem(self):
		for i in xrange(18):
			self.new_list.append(i)
		del self.new_list[16]
		self.assertEquals(
			str(self.new_list), 
			"{[0, 1, 2, 3, 4, 5, 6, 7], [8, 9, 10, 11, 12, 13, 14, 15, 17]}"
		)


	def test_reorder_delitem(self):
		for i in xrange(18):
			self.new_list.append(i)
		del self.new_list[0]
		del self.new_list[0]
		del self.new_list[0]
		del self.new_list[0]
		self.assertEquals(
			str(self.new_list), 
			"{[4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]}"
		)


	def test_contains(self):
		for i in xrange(22):
			self.new_list.append(i)
		self.assertTrue(5 in self.new_list);


	def test_iter(self):
		for i in xrange(4):
			self.new_list.append(i)
		j = 0
		for v in self.new_list:
			if not v == j:
				self.assertTrue(False)
				return
			j += 1
		self.assertTrue(True)


	def test_reverse(self):
		for i in xrange(4):
			self.new_list.append(i)
		j = 3
		for v in reversed(self.new_list):
			if not v == j:
				self.assertTrue(False)
				return
			j -= 1
		self.assertTrue(True)


	def test_add(self):
		for i in xrange(9):
			self.new_list.append(i+1)
		l = UnrolledLinkedList()
		for i in xrange(9):
			l.append(i+10)
		total = self.new_list + l
		self.assertEquals(str(total), "{[1, 2, 3, 4, 5, 6, 7, 8], [9, 10, 11, 12, 13, 14, 15, 16, 17, 18]}")


	def test_mul(self):
		for i in xrange(2):
			self.new_list.append(i)
		l = self.new_list * 3
		self.assertEquals(str(l), "{[0, 1, 0, 1, 0, 1]}")


	def test_invalid_mul(self):
		for i in xrange(2):
			self.new_list.append(i)
		self.assertRaises(TypeError, lambda: self.new_list * "r")




if __name__ == '__main__':
	unittest.main()



# TODO:
"""
	iter
	reversed
"""