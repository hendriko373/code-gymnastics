module Main where

import Test.QuickCheck
import Data.List (sort)

main :: IO ()
main = do
  quickCheck prop_halfAndDouble
  quickCheck (prop_halfAndDouble' :: Double -> Bool)
  quickCheck prop_sortedListIsOrdered
  quickCheck prop_sumIsAssociative
  quickCheck prop_sumIsCommutative
  quickCheck prop_reverseTwiceIsOriginal

  print "foldr (:) xs ys == (++) ys xs"
  quickCheck prop_appendFoldrConsEquality

  print "foldr (++) [] == concat"
  quickCheck prop_appendFoldrConsEquality

half x = x / 2
prop_halfAndDouble = 
  forAll (arbitrary :: Gen Double) 
    (\x -> ((*2) . half $ x) == x)
prop_halfAndDouble' x = 
    ((*2) . half $ x) == x

-- checks whether a list is ordered
listOrdered :: (Ord a) => [a] -> Bool
listOrdered xs =
  snd $ foldr go (Nothing, True) xs
  where go _ status@(_, False) = status
        go y (Nothing, t) = (Just y, t)
        go y (Just x, t) = (Just y, x >= y)
prop_sortedListIsOrdered =
  forAll (arbitrary :: Gen [Int])
    (\xs -> listOrdered $ sort xs)

prop_sumIsAssociative =
  forAll (arbitrary :: Gen (Integer, Integer, Integer))
    (\(x, y, z) -> x + (y + z) == (x + y) + z)
prop_sumIsCommutative =
  forAll (arbitrary :: Gen (Integer, Integer))
    (\(x, y) -> x + y == y + x)

prop_reverseTwiceIsOriginal xs =
  xs == (reverse $ reverse xs)
  where types = xs :: [Int]

prop_appendFoldrConsEquality =
  forAll (arbitrary :: Gen [Int])
    (\xs ys -> (foldr (:) ys xs) == (++) xs ys)

prop_concatFoldrAppendEquality =
  forAll (arbitrary :: Gen [[Int]])
    (\xs -> (foldr (++) [] xs) == concat xs)

data Fool = Fulse | Frue deriving (Eq, Show)
instance Arbitrary Fool where
  arbitrary = oneof [return Fulse, return Frue]

data Gool = Gulse | Grue deriving (Eq, Show)
instance Arbitrary Gool where
  arbitrary = frequency [(2, return Gulse), (1, return Grue)]