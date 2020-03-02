data Trivial = Trivial

-- Typeclass Eq instance declaration
-- provides the typeclass Eq for Trivial.
-- "Trivial has an instance of Eq"
-- or, loosely, "Trivial is an instance of Eq"
instance Eq Trivial where
    (==) Trivial Trivial = True

data Identity a = Id a

-- This only works if the type variable a
-- has an instance of Eq
instance Eq a => Eq (Identity a) where
    (==) (Id x) (Id y) = x == y

-- Exercises: Eq instances
-- 1.
data TisAnInteger = TisAn Integer
instance Eq TisAnInteger where
    (==) (TisAn x) (TisAn y) = x == y

-- 2.
data TwoIntegers = Two Integer Integer
instance Eq TwoIntegers where
    (==) (Two x1 y1) (Two x2 y2) = x1 == x2 && y1 == y2

-- 3.
data StringOrInt =
    TisAnInt Int | TisAString String
instance Eq StringOrInt where
    (==) (TisAnInt x) (TisAnInt y) = x == y
    (==) (TisAString x) (TisAString y) = x == y
    (==) _ _ = False

-- 4.
data Pair a = Pair a a
instance Eq a => Eq (Pair a) where
    (==) (Pair x1 y1) (Pair x2 y2) = x1 == x2 && y1 == y2

-- 5.
data Tuple a b = Tuple a b
instance (Eq a, Eq b) => Eq (Tuple a b) where
    (==) (Tuple x1 y1) (Tuple x2 y2) = x1 == x2 && y1 == y2

-- 6.
data Which a = ThisOne a | ThatOne a
instance (Eq a) => Eq (Which a) where
    (==) (ThisOne x) (ThisOne y) = x == y
    (==) (ThatOne x) (ThatOne y) = x == y
    (==) _ _ = False

-- 7.
data EitherOr a b = Hello a | Goodbye b
instance (Eq a, Eq b) => Eq (EitherOr a b) where
    (==) (Hello x) (Hello y) = x == y
    (==) (Goodbye x) (Goodbye y) = x == y
    (==) _ _ = False

-- Show
instance Show Trivial where
    show _ = "Trivial printed"
