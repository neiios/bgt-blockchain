# `rpc_block.py` example
from bitcoin.rpc import RawProxy
from pprint import pprint
import re
import hashlib
from binascii import unhexlify, hexlify

# Create a connection to local Bitcoin Core node
p = RawProxy()

# enter block with a check
max_height = p.getblockcount()
print("The highest block right now is " + str(max_height))
while True:
  try:
    block_height = input('Enter block height: ')
    block_height = int(block_height)
    if (block_height >= 0 and block_height <= max_height): break
    raise ValueError
  except ValueError:
    print("The number is invalid.")

blockhash = p.getblockhash(block_height)
block = p.getblock(blockhash)

def convert_num_to_le(num, len):
  return hexlify(num.to_bytes(len, "little")).decode("utf-8")

def convert_str_to_le(str):
  return hexlify(unhexlify(str)[::-1]).decode("utf-8")

def hash_block_header(str):
  # convert to bytes
  header_bin = unhexlify(str)
  # hash twice
  hash = hashlib.sha256(hashlib.sha256(header_bin).digest()).digest()
  return hexlify(hash[::-1]).decode("utf-8")

# header fields
version = convert_num_to_le(block['version'], 4)
if (block_height != 0): hashPrevBlock = convert_str_to_le(block['previousblockhash'])
else: hashPrevBlock = convert_str_to_le("0000000000000000000000000000000000000000000000000000000000000000")
hashMerkleRoot = convert_str_to_le(block['merkleroot'])
time = convert_num_to_le(block['time'], 4)
bits = convert_str_to_le(block['bits'])
nonce = convert_num_to_le(block['nonce'], 4)

# hash header
header = hash_block_header(version + hashPrevBlock + hashMerkleRoot + time + bits + nonce)
if (blockhash == header): print(f"The block hash is correct.")
else: print(f"The block hash is incorrect.")
print(f"Blockhash 1: {blockhash:>70}\nBlockhash 2: {header:>70}")

# DEBUG
# print(blockhash)
# pprint(block)
# print(version)
# print(hashPrevBlock)
# print(hashMerkleRoot)
# print(time)
# print(bits)
# print(nonce)
