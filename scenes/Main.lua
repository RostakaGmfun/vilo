print "In \"Main.lua\""


function create() 
    actor = vilo.Actor.New("Actor.lua", "Player")
    actor.sayHello()
end

function update(dt)
    actor.update(dt)
end

function destroy()
    actor.destroy()
end
