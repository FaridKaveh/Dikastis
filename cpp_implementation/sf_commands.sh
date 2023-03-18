#!/usr/bin/expect 
spawn /home/farid/Apps/stockfish_15_linux_x64_avx2/stockfish15
expect Stockfish
send "position fen rnb1kbnr/ppp1pppp/8/8/1q6/2N5/P1PP1PPP/1RBQKBNR b Kkq - 1 5 \n isready \n"
expect readyok
send "go depth 15 \n " 
expect bestmove 
send " isready \n"
expect readyok 
