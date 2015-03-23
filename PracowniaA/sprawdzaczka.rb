input = gets

def win!
  puts 'OK'
  exit 0
end

def fail!(a = nil, b = nil)
  fail "Expected #{a}, got #{b}"
end

win! if /BRAK/.match(input)
  
range = input.to_i - 1

cur = 0

(0..range).each do
  from,_,to = gets.split(' ').map(&:to_i)
  
  fail!(cur, from) unless cur == from

  cur = to
end

fail!(cur, 0) unless cur == 0

win!
