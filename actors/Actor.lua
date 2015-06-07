
health = 100
name = "Dude"

print "in Actor.lua"

function create()
    print "Actor.create()"
end

function update(dt)
    print(dt)
end

function destroy()

end

function sayHello()
    print ("[Actor.lua]Hello, my name is " .. name)
    print ("[Actor.lua]My hp is "..health)
end
