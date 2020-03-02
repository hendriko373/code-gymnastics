module Addition where

import Test.Hspec
import Test.QuickCheck

addTests :: IO ()
addTests = hspec $ do
  describe "Addition" $ do
    it "1 + 1 is greater than 1" $ do
      1 + 1 > 1 `shouldBe` True 
    it "2 + 2 is equal to 4" $ do
      2 + 2 == 4 `shouldBe` True 
    it "x + 1 is greater than 1" $ do
      property $ \x -> x + 1 > (x :: Int)

multTests :: IO ()
multTests = hspec $ do
  describe "Multiplication" $ do
    it "5 times 0 is equal to 0" $ do
      mult 5 0 `shouldBe` 0
    it "3 times 6 is equal to 18" $ do
      mult 3 6 `shouldBe` 18

mult :: (Eq a, Num a) => a -> a -> a
mult _ 0 = 0
mult n m = n + (mult n (m - 1))

genTuple :: (Arbitrary a, Arbitrary b) => Gen (a, b)
genTuple = do
  x <- arbitrary
  y <- arbitrary
  return (x, y)

genEither :: (Arbitrary a, Arbitrary b) => Gen (Either a b)
genEither = do
  x <- arbitrary
  y <- arbitrary
  elements [Left x, Right y]

genMaybe :: Arbitrary a => Gen (Maybe a)
genMaybe = do
  x <- arbitrary
  elements [Nothing, Just x]

genMaybe' :: Arbitrary a => Gen (Maybe a)
genMaybe' = do
  x <- arbitrary
  frequency [(1, return Nothing), (30, return (Just x))]

prop_additionGreater :: Int -> Bool
prop_additionGreater x = x + 1 > x

runQc :: IO ()
runQc = quickCheck prop_additionGreater