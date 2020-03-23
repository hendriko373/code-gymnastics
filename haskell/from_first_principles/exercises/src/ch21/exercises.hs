import Test.QuickCheck
import Test.QuickCheck.Checkers
import Test.QuickCheck.Classes

-- Identity
newtype Identity a = Identity a
    deriving (Eq, Show)

instance Functor Identity where
    fmap f (Identity a) = Identity $ f a

instance Foldable Identity where
    foldMap f (Identity a) = f a

instance Traversable Identity where
    traverse f (Identity a) = pure Identity <*> f a

-- Constant
newtype Constant a b = Constant a
    deriving (Eq, Show)

instance Functor (Constant a) where
    fmap _ (Constant a) = (Constant a)

instance Foldable (Constant a) where
    foldMap _ c = mempty

instance Traversable (Constant a) where
    traverse _ (Constant a) = pure $ (Constant a) 

-- Maybe
data Optional a =
    Nada
  | Yep a
  deriving (Show, Eq)

instance Functor Optional where
    fmap _ Nada = Nada
    fmap f (Yep a) = Yep $ f a

instance Foldable Optional where
    foldMap _ Nada = mempty
    foldMap f (Yep a) = f a

instance Traversable Optional where
    traverse _ Nada = pure Nada
    traverse f (Yep a) = Yep <$> f a -- pure Yep <*> f a

-- List
data List a =
    End
  | Cons a (List a)
  deriving (Eq, Show)

instance Functor List where
    fmap f End = End
    fmap f (Cons a as) = Cons (f a) $ fmap f as
    
instance Foldable List where
    foldMap _ End = mempty
    foldMap f (Cons a as) = f a <> foldMap f as

instance Traversable List where
    traverse _ End = pure End
    traverse f (Cons a as) = Cons <$> f a <*> traverse f as

fromList :: [a] -> List a
fromList = foldr Cons End

instance Arbitrary a => Arbitrary (List a) where
    arbitrary = do
        l <- arbitrary
        return $ fromList l

instance Eq a => EqProp (List a) where
    (=-=) = eq

testList = quickBatch $ traversable (undefined :: List (Int, Int, [Int]))

-- Three
data Three a b c = Three a b c
    deriving (Eq, Show)

instance Functor (Three a b) where
    fmap f (Three a b c) = Three a b $ f c

instance Foldable (Three a b) where
    foldMap f (Three a b c) = f c

instance Traversable (Three a b) where
    traverse f (Three a b c) = (Three a b) <$> f c

-- S
data S n a = S (n a) a
    deriving (Eq, Show)
    -- e.g. S [] Int

instance Functor n => Functor (S n) where
    fmap f (S m a) = S (fmap f m) $ f a

instance Foldable n => Foldable (S n) where
    foldMap f (S m a) = foldMap f m <> f a

instance Traversable n => Traversable (S n) where
    traverse f (S m a) = S <$> traverse f m <*> f a

-- Tree
data Tree a =
    Empty
  | Leaf a
  | Node (Tree a) a (Tree a)
  deriving (Eq, Show)

instance Functor Tree where
    fmap f Empty = Empty
    fmap f (Leaf a) = Leaf $ f a
    fmap f (Node tl a tr) = Node (f <$> tl) (f a) (f <$> tr) 

instance Foldable Tree where
    foldMap _ Empty = mempty
    foldMap f (Leaf a) = f a
    foldMap f (Node tl a tr) = 
        (foldMap f tl) <> (f a) <> (foldMap f tr)

instance Traversable Tree where
    traverse _ Empty = pure Empty
    traverse f (Leaf a) = Leaf <$> f a
    traverse f (Node tl a tr) =
        Node <$> traverse f tl <*> f a <*> traverse f tr