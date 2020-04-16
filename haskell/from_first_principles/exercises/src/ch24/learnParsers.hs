module LearnParsers where

import Text.Trifecta

stop :: Parser a
stop = unexpected "stop"

testParse :: Show a => Parser a -> IO ()
testParse p =
    print $ parseString p mempty "123"

one :: Parser Char
one = char '1'

one' :: Parser Char
one' = one >> stop

one'' = one >> eof

oneTwo :: Parser Char
oneTwo = char '1' >> char '2'

oneTwo' :: Parser Char
oneTwo' = oneTwo >> stop

oneTwo'' = oneTwo >> eof
oneTwoThree'' = oneTwo >> char '3' >> eof

pNL :: String -> IO ()
pNL s = putStrLn ('\n' : s)

main = do
    pNL "stop:"
    testParse (stop :: Parser Char)
    pNL "one:"
    testParse one
    pNL "one':"
    testParse one'
    pNL "one'':"
    testParse one''
    pNL "oneTwo:"
    testParse oneTwo
    pNL "oneTwo':"
    testParse oneTwo'
    pNL "oneTwo'':"
    testParse oneTwo''
    pNL "oneTwoThree'':"
    testParse oneTwoThree''

myFunc :: Parser Integer
--myFunc = integer >>= (\i -> eof >> return i)
myFunc = integer <* eof

