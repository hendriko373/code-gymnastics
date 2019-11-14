module Cipher where

import Data.Char

cipher :: Int -> String -> String
cipher n s = map 
    (\c -> 
        if elem c [' ','.', ',', '?', '!'] 
            then c
            else shift n c) 
    s

unCipher :: Int -> String -> String
unCipher n s = cipher (-n) s

shift :: Int -> Char -> Char
shift n c = chr $ mod ((ord c - b) + n) 26 + b
    where b = if isUpper c then ord 'A' else ord 'a'