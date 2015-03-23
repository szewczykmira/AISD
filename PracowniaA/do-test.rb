Dir['test/*'].each do |test|
  puts "Testing #{test}"

  o = `cat #{test} | time ./Main | ruby sprawdzaczka.rb`

  exit 1 unless /OK/.match(o)
  
  puts o
end
puts 'DONE'
