health = 100
name = "Dude"

function create()
    print "Actor.create()"
end

function update(dt)
    print dt
end

function destroy()

end

function sayHello()
    print "Hello, my name is"..name
end
