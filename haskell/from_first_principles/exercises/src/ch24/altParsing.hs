{-# LANGUAGE QuasiQuotes #-}

module AltParsing where

import Control.Applicative
import Text.RawString.QQ
import Text.Trifecta

type NumberOrString =
    Either Integer String
    
a = "blah"
b = "123"
c = "123blah789"

parseNos :: Parser NumberOrString
parseNos =
    skipMany (oneOf "\n\t ") >>
    (Left <$> integer)
    <|> (Right <$> some letter) >>=
    \r -> (skipMany (oneOf"\n\t ") >>
            return r)

eitherOr :: String
eitherOr = [r|
    123
    abc
    456
    def
    |]

main = do
    print $ parseString (some letter) mempty a
    print $ parseString integer mempty b
    print $ parseString parseNos mempty a
    print $ parseString parseNos mempty b
    print $ parseString (many parseNos) mempty c
    print $ parseString (some parseNos) mempty c
