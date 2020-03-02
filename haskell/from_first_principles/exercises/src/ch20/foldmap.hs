newtype Endo b = Endo
  { appEndo :: (b -> b)
  }

instance Monoid (Endo b) where
    mempty = Endo id
    mappend (Endo f) (Endo g) = Endo $ f . g

data List a =
    End
  | Cons a (List a)

instance Foldable List where
    foldMap :: Monoid m => (a -> m) -> List a -> m
    foldMap _ End         = mempty
    foldMap f (Cons a as) = (f a) <> foldmap f as 

    foldr f z xs = appEndo (foldmap (Endo . f) xs) z


