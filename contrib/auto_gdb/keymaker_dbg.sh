#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.keymakercore/keymakerd.pid file instead
keymaker_pid=$(<~/.keymakercore/testnet3/keymakerd.pid)
sudo gdb -batch -ex "source debug.gdb" keymakerd ${keymaker_pid}
