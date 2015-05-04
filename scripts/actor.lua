-- Actor script

--called on actor creation
--return: nothing
function create()
    print("In create")
    hello();
end

function add(a, b)
    return a+b
end

function greeting(name, age)
    print("Hello, "..name..". I guess you're "..age.." years old!" )
end

--called every tick (frame yeah)
--return:
-- 0 or nil - continue runnig actor
-- else - destroy the actor - will call dectroy() function
function update()
    print("On update")
end

function onKeyPress(key)
    print(key.." pressed")
end

function onKeyRelease(key)
    print(key.." released")
end

function onMousePress(button)
    print(button.." pressed")
end

function onMouseRelease(button)
    print(button.." released")
end

--called on actor destroy
--returns - nothing
function destroy()
    print("On Destroy")
end
