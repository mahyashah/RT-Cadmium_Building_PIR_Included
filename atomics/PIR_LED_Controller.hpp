/**
* By: Mahya
* ARSLab - Carleton University
*/

#ifndef BOOST_SIMULATION_PDEVS_PIR_LED_Controller_HPP
#define BOOST_SIMULATION_PDEVS_PIR_LED_Controller_HPP

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include <limits>
#include <math.h> 
#include <assert.h>
#include <memory>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <limits>
#include <random>


using namespace cadmium;
using namespace std;

//Port definition
    struct PIR_LED_Controller_defs {
        //Output ports
        struct out_r : public out_port<bool> { };
        struct out_g : public out_port<bool> { };
        
        //Input ports
        struct inpa : public in_port<bool> { };
        struct inpb : public in_port<bool> { };
        struct inpc : public in_port<bool> { };
  };

    template<typename TIME>
    class PIR_LED_Controller_Con {
        using defs=PIR_LED_Controller_defs; // putting definitions in context
        public:
            //Parameters to be overwriten when instantiating the atomic model
            
            // default constructor
            PIR_LED_Controller_Con() noexcept{
              state.type = false;
              state.input_a = false;
              state.input_b = false;
              state.input_c = false;
              state.output_r = false;
              state.output_g = false; 
            }
            
            // state definition
            struct state_type{
              bool type;
              bool input_a;
              bool input_b;
              bool input_c;
              bool output_r;
              bool output_g;
            }; 
            state_type state;
            // ports definition
            
            using input_ports=std::tuple<typename defs::inpa, typename defs::inpb, typename defs::inpc>;
            using output_ports=std::tuple<typename defs::out_r, typename defs::out_g>;

            // internal transition
            void internal_transition() {

              state.type = false;
              //Do nothing... 
            }

            // external transition
            void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) { 
               
              for(const auto &x : get_messages<typename defs::inpa>(mbs))
                state.input_a = (x == 1) ? 1 : 0;
                    
              for(const auto &x : get_messages<typename defs::inpb>(mbs))
                state.input_b = (x == 1) ? 1 : 0;  

              for(const auto &x : get_messages<typename defs::inpc>(mbs))
                state.input_c = (x == 1) ? 1 : 0;
              
              //cout << "Current state of the Room LED Controller In External transition:\n";
              ////cout << "a: " << state.input_a << " b: " << state.input_b << " c: " << state.input_c << " \n";
              ////cout << "e = " << e << "\n";
              

              if(state.input_a && state.input_b){
                //cout << "Case 1 \n";
                state.output_r = 1;
                state.output_g = 0;
              } 
              else if(state.input_a && state.input_c){                        
                //cout << "Case 2 \n";
                state.output_r = 1;
                state.output_g = 0;
                }

              else{             
                //cout << "Case 3 \n"   ;    
                state.output_r = 0;
                state.output_g = 1;
                }

              state.type = true;
            }

            // confluence transition
            void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
              internal_transition();
              external_transition(TIME(), std::move(mbs));
            }

            // output function
            typename make_message_bags<output_ports>::type output() const {
              typename make_message_bags<output_ports>::type bags;
              
              get_messages<typename defs::out_r>(bags).push_back(state.output_r);
              get_messages<typename defs::out_g>(bags).push_back(state.output_g);
              return bags;
            }

            // time_advance function
            TIME time_advance() const { 
              if(state.type)
                return TIME("00:00:00");
              return std::numeric_limits<TIME>::infinity();
            }

            friend std::ostringstream& operator<<(std::ostringstream& os, const typename PIR_LED_Controller_Con<TIME>::state_type& i) {
              os << "Current state: " << i.type; 
              return os;
            }
        };     


#endif // BOOST_SIMULATION_PDEVS_PIR_LED_Controller_HPP
