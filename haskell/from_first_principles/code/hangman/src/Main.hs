module Main where

import Control.Monad (forever)
import Data.Char (toLower)
import Data.Maybe (isJust)
import Data.List (intersperse)
import System.Exit (exitSuccess)
import System.Random (randomRIO)

main :: IO ()
main = do
  putStrLn "Welcome to the Hangman game!"
  putStrLn $ "Randomly choosing a word..."
  word <- gameWords >>= randomWord
  runGame $ freshPuzzle word

type WordList = [String]

allWords :: IO WordList
allWords = do
  dict <- readFile "data/dict.txt"
  return (lines dict)

minWordLength :: Int
minWordLength = 5

maxWordLength :: Int
maxWordLength = 9

gameWords :: IO WordList
gameWords = do
  aw <- allWords
  return (filter f aw)
  where f w = 
          l >= minWordLength && l <= maxWordLength
          where l = length w

randomWord :: WordList -> IO String
randomWord wl = do
  i <- randomRIO (0, length wl - 1)
  return $ wl !! i

data Puzzle = Puzzle String [Maybe Char] [Char]

instance Show Puzzle where
  show (Puzzle _ discovered guessed) =
    (intersperse ' ' $ map renderPuzzleChar discovered)
    ++ " |> Guessed so far: " ++ guessed 
    where renderPuzzleChar Nothing  = '_'
          renderPuzzleChar (Just c) = c

freshPuzzle :: String -> Puzzle
freshPuzzle s = Puzzle s (map (\c -> Nothing) s) []

charInWord :: Puzzle -> Char -> Bool
charInWord (Puzzle s _ _) c = elem c s

alreadyGuessed :: Puzzle -> Char -> Bool
alreadyGuessed (Puzzle _ _ guessed) c = elem c guessed

fillInCharacter :: Puzzle -> Char -> Puzzle
fillInCharacter (Puzzle goal discovered guessed) c =
  Puzzle goal discovered' (c:guessed)
  where discovered' = zipWith (zipper c) goal discovered
        zipper c' cg cd
          | c' == cg  = Just c'
          | otherwise = cd

handleGuess :: Puzzle -> Char -> IO Puzzle
handleGuess p c = do
  putStrLn $ "Your guess was " ++ [c]
  case (charInWord p c
      , alreadyGuessed p c) of
    (_, True) -> do
      putStrLn "Already guessed that letter. Pick another one!"
      return p
    (True, _) -> do
      putStrLn "You found a letter!"
      return $ fillInCharacter p c
    (False, _) -> do
      putStrLn "Letter not in word. Guess again."
      return $ fillInCharacter p c

gameOver :: Puzzle -> IO ()
gameOver (Puzzle goal _ guessed) =
  if length guessed > 7 then
    do putStrLn "Game over!"
       putStrLn $ "The word was " ++ goal
       exitSuccess
  else return ()

gameWin :: Puzzle -> IO ()
gameWin (Puzzle _ discovered _) =
  if all isJust discovered then
    do putStrLn "You win!"
       exitSuccess
  else return ()

runGame :: Puzzle -> IO ()
runGame puzzle = forever $ do
  gameOver puzzle
  gameWin puzzle
  putStrLn $ "Current puzzle is: " ++ show puzzle
  putStr "Guess a letter: "
  guess <- getLine
  case guess of
    [c] -> handleGuess puzzle c >>= runGame
    _   -> putStrLn "Must be single character!"
