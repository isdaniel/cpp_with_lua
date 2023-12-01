--t = "Hello World"
--n = "Daniel"
--f = "Shih"
--l = 100


function Add(a, b)
    print("Lua function Add(".. a ..", ".. b ..") called")
    return a * b
end

function DoSomething(a,b)
	print("Lua function DoSomething(".. a ..", ".. b ..") called\n")

    c = Cpp_Function(a + 100 ,b)

    return c;
end
