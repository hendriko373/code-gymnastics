newtype Endo b = Endo
  { appEndo :: (b -> b)
  }

instance Semigroup (Endo b) where
    (Endo f) <> (Endo g) = Endo $ f . g

instance Monoid (Endo b) where
    mempty = Endo id

data List a =
    End
  | Cons a (List a)
  deriving (Show, Eq)

toList :: [a] -> List a
toList [] = End
toList (a:as) = Cons a (toList as)

instance Foldable List where
    foldMap _ End         = mempty
    foldMap f (Cons a as) = (f a) <> foldMap f as 

    foldr f z xs = appEndo (foldMap (Endo . f) xs) z
