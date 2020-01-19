import textwrap
import binascii
import sys

print textwrap.wrap((binascii.hexlify(sys.argv[1][::-1]).decode()), 8)
