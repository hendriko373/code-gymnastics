{-# LANGUAGE InstanceSigs #-}
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

-- Reader
newtype Reader r a =
    Reader { runReader :: r -> a}

instance Functor (Reader r) where
    fmap :: (a -> b) -> Reader r a -> Reader r b
    fmap f (Reader g) = Reader $ f . g

instance Applicative (Reader r) where
    pure :: a -> (Reader r a)
    pure a = Reader $ const a

    (<*>) :: Reader r (a -> b) -> Reader r a -> Reader r b
    (Reader rf) <*> (Reader ra) = Reader $ \r -> (rf r) (ra r)

instance Monad (Reader r) where
    return :: a -> Reader r a
    return = pure

    (>>=) :: Reader r a -> (a -> Reader r b) -> Reader r b
    (Reader ra) >>= f = Reader $ \r -> runReader (f (ra r)) r

ask :: Reader a a
ask = Reader id

myLiftA2 :: Applicative f => (a -> b -> c) -> f a -> f b -> f c
myLiftA2 = ((<*>) .) . (<$>)
-- myLiftA2 g fa fb = g <$> fa <*> fb

asks :: (r -> a) -> Reader r a
asks f = Reader f

