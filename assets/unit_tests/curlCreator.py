import math

curl_rad = .1
curl_freq = 20

hair_len = 3
n_points = 1000
n_points_per_curl = n_points / curl_freq

delta_theta = 2 * math.pi / n_points_per_curl

hair_curl = []




f = open("assets/unit_tests/tight_curl.xml", "w")

towrite = """
	<scene dim="3" ctcd="0"> 
	<simtype type="DiscreteElasticRods"/>

	<description text="Two strands hanging."/>
	<camera dist="10.24041" radius="1.79232" fov="40">
		<rotation x="-0.0762453" y="-0.38702" z="-0.0352307" w="0.918238"/>
		<center x="-0.304586" y="-0.936187" z="-0.472652"/>
	</camera>
	<duration time="1.0"/>
	<integrator type="preconditioned-compliant-euler" maxnewton="0" maxiters="50" criterion="1e-4"/>
	<collision type="none" COR="0.0" ctcd="1"/>

	<fluidsim oy="-3.0" ox="-3.0" oz="-0.46875" width="6.0" gx="96" gy="96" gz="15" init="none" rl="0.6" drawgrid="0">
		<boundary type="box" cx="2.447" cy="0.0" cz="0.0" ex="0.15" ey="0.15" ez="0.15" radius="0.05" inside="0"/>
		<boundary type="box" cx="-2.21004600000000" cy="0.161002000000000" cz="-0.118655000000000" ex="0.15" ey="0.15" ez="0.15" radius="0.05" inside="0"/>
	</fluidsim>
 
	<camera dist="5.56999" radius="1.90505" fov="40">
		<rotation x="0" y="0" z="0" w="1"/>
		<center x="0.0124827" y="-1.49237" z="0"/>
	</camera>

	<StrandParameters> 
		<radius value="0.0037" /> 
		<youngsModulus value="3.9e10" /> 
		<shearModulus value="3.4e9" /> 
		<density value="1.32" /> 
		<viscosity value="1e8" /> 
		<baseRotation value="0.0"/>    
		<accumulateWithViscous value="1" /> 
		<accumulateViscousOnlyForBendingModes value="0" /> 
	</StrandParameters> 

	<script target="root" type="absorption" x="0" y="0" z="0" w="0.01" start="0.0" end="0.5"/>    

	<StrandMaterialForces params="0" flow="shallow"> 
	"""
f.write(towrite)

for i in range(n_points):
	x = i * hair_len / n_points
	y = curl_rad * math.cos(delta_theta * (i % n_points_per_curl))
	z = curl_rad * math.sin(delta_theta * (i % n_points_per_curl))

	f.write("<particle x=\"" + str(x) + " " + str(y) + " " + str(z) + "\" v=\"0.0 0.0 0.0\" eta=\"0.0\"") 

	if i == 0 or i==1:
		f.write(" fixed=\"1\"")

	f.write(" /> \n")

file_end = """
	</StrandMaterialForces> 

	</scene> 
	"""
f.write(file_end)

f.close()


