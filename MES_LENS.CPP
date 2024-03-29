// C++ Source Code Generated by XSI Shader Wizard

////////////////////////////////////////////////////////////////
// Includes

#include <shader.h>
//#include "mes_lens.h"

////////////////////////////////////////////////////////////////
//header
typedef struct
{
	int					int1;
	miScalar			scalar1;
	miScalar			scalar2;
	miScalar			scalar3;
} mes_lens_t;



// Implementation

extern "C" DLLEXPORT miBoolean
mes_lens
(
	miColor				*result,
	miState				*state,
	mes_lens_t			*params
	)
{
    miVector       dir, myorg, focalpoint;
    myorg = state->org;
    dir = state->dir; //initial direction does not depend on our modified dir
    
    
    //convert our vectors to camera space
    
    mi_point_to_camera(state, &myorg, &myorg);
    mi_vector_to_camera(state, &dir, &dir);
    
    //get the params right
    miScalar param1 = *mi_eval_scalar(&params->scalar1);  // adjust the state->org
    miScalar param2 = *mi_eval_scalar(&params->scalar2); // adjust the state->dir
    miScalar param3 = *mi_eval_scalar(&params->scalar3); // distance out to our imaginary focal point
    
    
    // set our imaginary focal point
       focalpoint.x = focalpoint.y = 0.0;
       focalpoint.z = -param3; // third slider will be focal distance
         
         
   //decide whether we are on the right side of the screen or the left
    if(state->raster_x < (state->camera->x_resolution/2.0f))
        {//  left side
        myorg.x = myorg.x - (param1/10);
        }
        
    else
        { // right side
        myorg.x = myorg.x + (param1/10);
        }
        
        
    // calculate dir based on vector from org to focalpoint
        dir.x += -myorg.x; //add the origin offset to the direction so they are orthagonal
        // now calculate a toe-in based on the vector to the far point.
        if(state->raster_x < (state->camera->x_resolution/2.0f))
        {
            myorg.x -= (param3/10);
        }
        else
        {
            myorg.x += (param3/10);
        }
        
        
        //convert from camera space back to world space and write out the ray
        mi_point_from_camera(state, &myorg,&myorg);
        mi_vector_from_camera(state, &dir, &dir);
        
        // call the trace, place the color value into return.
        (void)mi_trace_eye(result, state, &myorg, &dir);
    
        //result->r += 0.25f;
        //result->r += myorg.x/10  ;
        //result->g += myorg.y/10 ;
        //result->b += dir.x;
        
	return( miTRUE );
}


extern "C" DLLEXPORT int
mes_lens_version( )
{
	return( 1 );
}
