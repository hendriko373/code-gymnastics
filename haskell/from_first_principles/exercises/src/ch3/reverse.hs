module Reverse where

import Data.List

-- Exerices 5 and 6 of chapter 3

rvrs :: String -> String
rvrs x = glue ( revlist $ split x ' ' ) ' '

-- split a string in a list given separator
split :: [Char] -> Char -> [[Char]]
split x v
    | not $ elem v x = [x]
    | otherwise = take i x : split (drop (i + 1) x) v
        where i = head $ findIndices (\e -> e == v) x

-- concat a list of strings with given separator
glue :: [[Char]] -> Char -> [Char]
glue [x] v = x
glue (x:xs) v = x ++ " " ++ glue xs v

-- reverse a list
revlist :: [a] -> [a]
revlist [] = []
revlist (x:xs) = revlist xs ++ [x]
