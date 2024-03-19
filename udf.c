//#include "udf.h"

DEFINE_ADJUST(calculate_udm, domain)
{
    Thread *cell_thread;
    cell_t cell_index;

    real rho = C_R(cell, cell_thread); // Retrieve density
    real mu = C_MU_L(cell, cell_thread); // Retrieve dynamic viscosity
    real nu_t = C_UDMI(cell_index, cell_thread, UDM_ARST11) / (2.0 * rho); // Assuming UDM_ARST11 stores (2.0*rho*nu_t*du1dx1)
    real mu_THETA = C_UDMI(cell_index, cell_thread, UDM_ARST12); // Assuming UDM_ARST12 stores mu_THETA
    real THETA = C_UDMI(cell_index, cell_thread, UDM_ARST13); // Assuming UDM_ARST13 stores THETA
    real G11 = C_UDMI(cell_index, cell_thread, UDM_ARST14); // Assuming UDM_ARST14 stores G11
    real k = C_UDMI(cell_index, cell_thread, UDM_ARST15); // Assuming UDM_ARST15 stores k

   // real du1dx1 = 
   // real du1dx2 = 

    real term1 = 2.0 * rho * nu_t * du1dx1;
    real term2 = mu_THETA * THETA * G11;
    real term3 = - (2.0 / 3.0) * rho * k;

    C_UDMI(cell_index, cell_thread, UDM_ARST11) = term1 + term2 + term3;
}
