module Exercises where

import Test.QuickCheck
import Test.QuickCheck.Checkers
import Test.QuickCheck.Classes

-- 1
data Pair a = Pair a a deriving (Show, Eq)

instance Functor Pair where
    fmap f (Pair a1 a2) = Pair (f a1) (f a2)

instance Applicative Pair where
    pure x = Pair x x 
    (Pair f1 f2) <*> (Pair x1 x2) = Pair (f1 x1) (f2 x2) 

instance Arbitrary a => Arbitrary (Pair a) where
    arbitrary = do
        a <- arbitrary
        return $ Pair a a

instance Eq a => EqProp (Pair a) where
    (=-=) = eq

testPair = quickBatch $ applicative (undefined :: Pair (String, String, Int))