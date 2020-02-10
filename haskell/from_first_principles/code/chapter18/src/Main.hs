module Main where

import Test.QuickCheck
import Test.QuickCheck.Checkers
import Test.QuickCheck.Classes

data Sum a b =
    First a
  | Second b
  deriving (Eq, Show)

instance Functor (Sum a) where
  fmap _ (First a)  = First a
  fmap f (Second b) = Second $ f b

instance Applicative (Sum a) where
  pure = Second
  (First a) <*> _ = First a
  (Second f) <*> s = fmap f s

instance Monad (Sum a) where
  (First a) >>= _ = First a
  (Second a) >>= f = f a

instance (Eq a, Eq b) => EqProp (Sum a b) where
  (=-=) = eq

instance (Arbitrary a, Arbitrary b) => Arbitrary (Sum a b) where
  arbitrary = do
    a <- arbitrary
    b <- arbitrary
    frequency [(1, return $ First a), (1, return $ Second b)]

testSum = quickBatch $ monad (undefined :: Sum String (String, String, Int))

main = do
  putStrLn "Test"
