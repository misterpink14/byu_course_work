import unittest
from unrolled_linked_list import UnrolledLinkedList


class CheckImplementation(unittest.TestCase):
    """ Check that the list has all the required functionality """

    def test_dunder_functions_exist(self):
        ull = UnrolledLinkedList()
        self.assertTrue(hasattr(ull, '__delitem__'))
        self.assertTrue(hasattr(ull, '__getitem__'))
        self.assertTrue(hasattr(ull, '__setitem__'))
        self.assertTrue(hasattr(ull, '__iter__'))
        self.assertTrue(hasattr(ull, '__str__'))
        self.assertTrue(hasattr(ull, '__len__'))
        self.assertTrue(hasattr(ull, '__contains__'))
        self.assertTrue(hasattr(ull, '__add__'))
        self.assertTrue(hasattr(ull, '__mul__'))

    def test_other_functions_exist(self):
        ull = UnrolledLinkedList()
        self.assertTrue(hasattr(ull, 'append'))

    def test_properties_exist(self):
        ull = UnrolledLinkedList()
        self.assertTrue(hasattr(ull, 'max_node_capacity'))


class SpotCheck(unittest.TestCase):

    def test_empty(self):
        list_five = UnrolledLinkedList(max_node_capacity=3)
        self.assertEqual(str(list_five), "{}")
        list_five.append(1)
        del list_five[0]
        self.assertEqual(str(list_five), "{}")

    def test_get_item_with_negative_index(self):
        ull = UnrolledLinkedList()
        ull.append(5)
        ull.append(10)
        self.assertEqual(2, len(ull))
        self.assertEqual('{[5, 10]}', str(ull))

        self.assertEqual(5, ull[-2])
        self.assertEqual(10, ull[-1])

        # test out of bounds
        with self.assertRaises(IndexError):
            ull[-1000000]

    def test_set_item_positive_index(self):
        ull = UnrolledLinkedList(max_node_capacity=3)
        self.assertEqual(0, len(ull))
        ull.append(5)
        ull.append(10)
        ull.append(3)
        ull.append(8)
        ull.append(1)
        self.assertEqual(5, len(ull))
        self.assertEqual('{[5, 10], [3, 8, 1]}', str(ull))

        ull[0] = 0
        self.assertEqual(5, len(ull))
        self.assertEqual(0, ull[0])
        self.assertEqual('{[0, 10], [3, 8, 1]}', str(ull))

        ull[1] = 1
        self.assertEqual(5, len(ull))
        self.assertEqual(1, ull[1])
        self.assertEqual('{[0, 1], [3, 8, 1]}', str(ull))

    def test_del_item_with_max_six(self):
        '''
            RULES FOR DELETING
            When an element is deleted from the list it is simply removed
            from the array. If the number of elements in the array falls below
            N/2, we take the elements from a neighboring array to fill the
            array. If neighboring array also has N/2 elements then we merge
            both of the arrays.

            in Python integer division rounds down
            3 / 2 = 1
        '''
        ull = UnrolledLinkedList(max_node_capacity=6)
        for x in range(0, 20):
            ull.append(x)
        self.assertEqual(20, len(ull))
        self.assertEqual('{[0, 1, 2], [3, 4, 5], [6, 7, 8], [9, 10, 11], [12, 13, 14], [15, 16, 17, 18, 19]}', str(ull))

        # delete middle of a node.
        # node size will be 2 which is < 3, so should readjust
        del ull[4]
        self.assertEqual(19, len(ull))
        self.assertEqual('{[0, 1, 2], [3, 5, 6, 7, 8], [9, 10, 11], [12, 13, 14], [15, 16, 17, 18, 19]}', str(ull))

        # delete last element
        # size of node will be 4 which is > 3 so no adjust
        del ull[-1]
        self.assertEqual(18, len(ull))
        self.assertEqual('{[0, 1, 2], [3, 5, 6, 7, 8], [9, 10, 11], [12, 13, 14], [15, 16, 17, 18]}', str(ull))

        # delete first element
        # node size will be 2 which is < 3, so should readjust
        del ull[0]
        self.assertEqual(17, len(ull))
        self.assertEqual('{[1, 2, 3], [5, 6, 7, 8], [9, 10, 11], [12, 13, 14], [15, 16, 17, 18]}', str(ull))

    def contains_test(self):
        list_one = UnrolledLinkedList(max_node_capacity=8)

        list_one.append(5)
        list_one.append(6)
        list_one.append(7)
        list_one.append(8)
        list_one.append(9)

        self.assertTrue(5 in list_one)
        self.asserTrue(8 in list_one)
        self.assertFalse(100 in list_one)

    def test_set_item_negative_index(self):
        ull = UnrolledLinkedList(max_node_capacity=3)
        self.assertEqual(0, len(ull))
        ull.append(5)
        ull.append(10)
        ull.append(3)
        ull.append(8)
        ull.append(1)
        self.assertEqual(5, len(ull))
        self.assertEqual('{[5, 10], [3, 8, 1]}', str(ull))

        ull[-5] = 0
        self.assertEqual(5, len(ull))
        self.assertEqual(0, ull[0])
        self.assertEqual('{[0, 10], [3, 8, 1]}', str(ull))

        ull[-4] = 1
        self.assertEqual(5, len(ull))
        self.assertEqual(1, ull[1])
        self.assertEqual('{[0, 1], [3, 8, 1]}', str(ull))

    def test_complex_add(self):
        ull1 = UnrolledLinkedList()
        ull2 = UnrolledLinkedList()

        ull1.append(1)
        ull1.append(2)
        ull1.append(3)
        ull1.append(4)
        self.assertEqual(4, len(ull1))

        ull2.append(10)
        ull2.append(20)
        ull2.append(30)
        ull2.append(40)
        self.assertEqual(4, len(ull2))

        # must rebalance
        ull3 = ull1 + ull2
        self.assertEqual(8, len(ull3))
        self.assertEqual('{[1, 2, 3, 4, 10, 20, 30, 40]}', str(ull3))

    def test_insert_with_max_three(self):
        # test with node size of 3
        ull = UnrolledLinkedList(max_node_capacity=3)
        self.assertEqual(0, len(ull))
        ull.append(5)
        self.assertEqual(1, len(ull))
        self.assertEqual('{[5]}', str(ull))
        ull.append(10)
        self.assertEqual(2, len(ull))
        self.assertEqual('{[5, 10]}', str(ull))
        ull.append(3)
        self.assertEqual(3, len(ull))
        self.assertEqual('{[5, 10, 3]}', str(ull))
        ull.append(8)
        self.assertEqual(4, len(ull))
        self.assertEqual('{[5, 10], [3, 8]}', str(ull))
        ull.append(1)
        self.assertEqual(5, len(ull))
        self.assertEqual('{[5, 10], [3, 8, 1]}', str(ull))

    def test_insert_with_max_four(self):
        ull = UnrolledLinkedList(max_node_capacity=4)
        self.assertEqual(0, len(ull))
        ull.append(5)
        self.assertEqual(1, len(ull))
        self.assertEqual('{[5]}', str(ull))
        ull.append(10)
        self.assertEqual(2, len(ull))
        self.assertEqual('{[5, 10]}', str(ull))
        ull.append(3)
        self.assertEqual(3, len(ull))
        self.assertEqual('{[5, 10, 3]}', str(ull))
        ull.append(8)
        self.assertEqual(4, len(ull))
        self.assertEqual('{[5, 10, 3, 8]}', str(ull))
        ull.append(1)
        self.assertEqual(5, len(ull))
        self.assertEqual('{[5, 10], [3, 8, 1]}', str(ull))

if __name__ == '__main__':
    unittest.main()
