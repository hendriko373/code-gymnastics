module Exercises where

import Data.Monoid
import Test.QuickCheck
import Test.QuickCheck.Gen.Unsafe

-- First
newtype First' a = First' (Maybe a)
    deriving (Eq, Show)

instance Semigroup (First' a) where
    (<>) (First' Nothing) x = x
    (<>) x y = x

instance Monoid (First' a) where
    mempty = (First' Nothing)

isAssociative :: (Eq a, Semigroup a) => a -> a -> a -> Bool
isAssociative x y z = (x <> y) <> z == x <> (y <> z)

leftId :: (Eq a, Monoid a) => a -> Bool
leftId x = mempty <> x == x

rightId :: (Eq a, Monoid a) => a -> Bool
rightId x = x <> mempty == x

instance Arbitrary a => Arbitrary (First' a) where
    arbitrary = do
        x <- arbitrary
        frequency 
            [(1, return $ First' Nothing)
           , (3, return $ First' (Just x))]

-- Semigroup exercises
-- 1
data Trivial = Trivial deriving (Eq, Show)

instance Semigroup Trivial where
    Trivial <> Trivial = Trivial

instance Arbitrary Trivial where
    arbitrary = return Trivial

-- 2
newtype Identity a = Identity a deriving (Eq, Show)

instance Semigroup a => Semigroup (Identity a) where
    (Identity a1) <> (Identity a2) = Identity (a1 <> a2)

instance Arbitrary a => Arbitrary (Identity a) where
    arbitrary = do
        a <- arbitrary
        return (Identity a)

-- 3
data Two a b = Two a b deriving (Eq, Show)

instance (Semigroup a, Semigroup b) => Semigroup (Two a b) where
    (Two a1 b1) <> (Two a2 b2) = Two (a1 <> a2) (b1 <> b2)

instance (Arbitrary a, Arbitrary b) => Arbitrary (Two a b) where
    arbitrary = do
        a <- arbitrary
        b <- arbitrary
        return (Two a b)

-- 8
data Or a b = Fst a | Snd b deriving (Eq, Show)

instance Semigroup (Or a b) where
    Snd b <> _ = Snd b
    Fst a <> x = x 

instance (Arbitrary a, Arbitrary b) => Arbitrary (Or a b) where
    arbitrary = do
        a <- arbitrary
        b <- arbitrary
        frequency [(1, return $ Fst a), (1, return $ Snd b)]

-- 9
data Combine a b =
    Combine { unCombine :: (a -> b) }

instance Show (Combine a b) where
    show _ = "default show for Combine" 

instance Semigroup b => Semigroup (Combine a b) where
    (Combine f) <> (Combine g) = Combine(\x -> f x <> g x)

instance (CoArbitrary a, Arbitrary b) => Arbitrary (Combine a b) where
    arbitrary = do
        f <- arbitrary
        return $ Combine f

($$) :: (Combine a b) -> a -> b
($$) (Combine f) x = f x

isCombineAssociative :: (Arbitrary a, Show a, Eq b, Semigroup b) =>
    (Combine a b)
    -> (Combine a b)
    -> (Combine a b)
    -> Property
isCombineAssociative c1 c2 c3
    = forAll 
        (vector 200)
        (\v -> 
            all (\x -> (c1 <> c2) $$ x <> c3 $$ x
                    == c1 $$ x <> (c2 <> c3) $$ x) v)

-- 11
data Validation a b = 
    Fail a 
  | Succ b deriving (Eq, Show)

instance Semigroup a => Semigroup (Validation a b) where
    (<>) (Fail f) (Succ s) = Fail f
    (<>) (Succ s) (Fail f) = Fail f
    (<>) (Fail f) (Fail g) = Fail (f <> g)
    (<>) (Succ s) (Succ t) = Succ (s)

instance (Arbitrary a, Arbitrary b) => Arbitrary (Validation a b) where
    arbitrary = do
        a <- arbitrary
        b <- arbitrary
        frequency [(1, return $ Fail a), (1, return $ Succ b)]

test :: IO ()
test = do
    print "Testing monoid laws for First ..."
    quickCheck (isAssociative :: (First' Int) -> (First' Int) -> (First' Int) -> Bool)
    quickCheck (leftId :: (First Int) -> Bool)
    quickCheck (rightId :: (First Int) -> Bool)

    print "Testing semigroup associativity for Trivial ..."
    quickCheck (isAssociative :: Trivial -> Trivial -> Trivial -> Bool)

    print "Testing semigroup associativity for Identity ..."
    quickCheck (isAssociative :: (Identity String) -> (Identity String) -> (Identity String) -> Bool)

    print "Testing semigroup associativity for Two ..."
    quickCheck (isAssociative :: (Two String (Sum Int)) -> (Two String (Sum Int)) -> (Two String (Sum Int)) -> Bool)

    print "Testing semigroup associativity for Or ..."
    quickCheck (isAssociative :: (Or String Int) -> (Or String Int) -> (Or String Int) -> Bool)

    print "Testing semigroup associativity for Validation ..."
    quickCheck 
        (isAssociative :: (Validation String Int) -> (Validation String Int) -> (Validation String Int) -> Bool)

    print "Testing semigroup associativity for Combine ..."
    quickCheck 
       (isCombineAssociative :: (Combine String (Sum Int)) -> (Combine String (Sum Int)) -> (Combine String (Sum Int)) -> Property)