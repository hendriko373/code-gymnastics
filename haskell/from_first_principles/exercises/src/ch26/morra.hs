import Control.Monad
import Control.Monad.Trans.Class
import Control.Monad.Trans.State.Lazy
import Control.Monad.IO.Class
import System.Random

data Score = Score
    { p1 :: Integer
    , p2 :: Integer }
    deriving Show

update :: Bool -> Score -> Score
update b (Score p1 p2) = 
    if b 
       then Score (p1 + 1) p2
       else Score p1 (p2 + 1)

play :: StateT Score IO ()
play = do
    lift $ putStr "P: "
    p1 <- lift getLine
    unless (p1 == "q") $ do
        lift $ putStr "C: "
        p2 <- lift $ randomRIO (1, 2)
        lift $ putStrLn $ show (p2 :: Integer)
        let p1wins = mod (read p1 + p2) 2 == 0
        modify $ \s -> update p1wins s
        lift $ putStrLn $ 
            "- " ++ (if p1wins then "P" else "C") ++ " wins" 
        play

main :: IO ()
main = do
    score <- execStateT play (Score 0 0)
    print score
