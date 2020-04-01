import Data.Char
import Control.Applicative

cap :: [Char] -> [Char]
cap xs = map toUpper xs

rev :: [Char] -> [Char]
rev xs = reverse xs

composed :: [Char] -> [Char]
composed = rev . cap

fmapped :: [Char] -> [Char]
fmapped = fmap rev cap

tupledA :: [Char] -> ([Char], [Char])
tupledA = (,) <$> cap <*> rev
-- (,) <$> cap :: [Char] -> a -> ([Char], a)

tupledA2 = liftA2 (,) cap rev

tupledM :: [Char] -> ([Char], [Char])
tupledM = do
    a <- cap
    b <- rev
    return (a, b)

tupledM2 = cap >>=
    (\a -> rev >>=
        (\b -> return (a, b)))
