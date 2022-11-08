# `rpc_block.py` example
from bitcoin.rpc import RawProxy
from pprint import pprint
import re

def main():
  # Create a connection to local Bitcoin Core node
  p = RawProxy()

  # coinbase
  # txid = "0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098"
  # original
  # txid = "0627052b6f28912f2703066a912ea577f2ce4da4caa5a5fbd8a57286c345c2f2"
  # biggest
  # txid = "4410c8d14ff9f87ceeed1d65cb58e7c7b2422b2d7529afc675208ce2ce09ed7d"

  # enter transaction with a check
  while True:
    txid = input('Enter transaction id: ')
    match = re.search(r'^[a-fA-F0-9]{64}$', txid)
    if (match): break

  raw_tx = p.getrawtransaction(txid)
  decoded_tx = p.decoderawtransaction(raw_tx)
  # pprint(decoded_tx)

  # find transaction output
  txsum = 0
  for transfer in decoded_tx['vout']:
    txsum += transfer['value']
  # pprint(txsum)

  # find input
  # pprint(decoded_tx['vin'])
  ptxsum = 0
  flag = False
  for vintx in decoded_tx['vin']:
    # dont bother checking if transaction has no inputs
    if vintx.get("coinbase", None) == None:
      flag = True
      ptxid = vintx['txid']
      ptxvoutn = vintx['vout']
      ptx = p.decoderawtransaction(p.getrawtransaction(ptxid))
      ptxsum += ptx['vout'][ptxvoutn]['value']

  # print fee
  if flag:
    print("Input sum", ptxsum)
    print("Output sum", txsum)
    print("Fee is", ptxsum - txsum, 'BTC')
  else:
    print("Coinbase transaction detected. No fee.")

if __name__ == "__main__":
  main()
