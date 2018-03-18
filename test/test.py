import teager

from unittest import TestCase

class TeagerTests(TestCase):
    def test_c(self):
        teager.parse_file("test/files/test_c.c")

