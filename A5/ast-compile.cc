#include "symbol-table.hh"
#include "ast.hh"
#include "local-environment.hh"
#include "icode.hh"
#include "reg-alloc.hh"
template class Number_Ast<double>;
template class Number_Ast<int>;

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register) {

}


Code_For_Ast & Assignment_Ast::compile() {

}


Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


Code_For_Ast & Name_Ast::compile() {
	Mem_Addr_Opd *opd1  = new Mem_Addr_Opd(*this->variable_symbol_entry);
	Register_Descriptor *rd;
	if(this->variable_symbol_entry->get_data_type() == int_data_type)
		rd = machine_desc_object.get_new_register<gp_data>();
	else if(this->variable_symbol_entry->get_data_type() == double_data_type)
		rd = machine_desc_object.get_new_register<float_reg>();
	Register_Addr_Opd *result = new Register_Addr_Opd(rd);
	Move_IC_Stmt *load_stmt = new Move_IC_Stmt(load, opd1, result);
	Code_For_Ast *output = new Code_For_Ast();
	output->set_reg(rd);
	output->append_ics(*load_stmt);
	return *output;
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register) {

}

template <class T>
Code_For_Ast & Number_Ast<T>::compile() {
	Const_Opd<T> *opd1  = new Const_Opd<T>(this->constant);
	Register_Descriptor *rd;
	if(this->get_data_type() == int_data_type)
		rd = machine_desc_object.get_new_register<gp_data>();
	else if(this->get_data_type() == double_data_type)
		rd = machine_desc_object.get_new_register<float_reg>();
	Register_Addr_Opd *result = new Register_Addr_Opd(rd);
	Move_IC_Stmt *load_stmt = new Move_IC_Stmt(load, opd1, result);
	Code_For_Ast *output = new Code_For_Ast();
	output->set_reg(rd);
	output->append_ics(*load_stmt);
	return *output;
}


template <class T>
Code_For_Ast & Number_Ast<T>::compile_and_optimize_ast(Lra_Outcome & lra) {

}


Code_For_Ast & Plus_Ast::compile() {
	Register_Addr_Opd *lhs_result = new Register_Addr_Opd(this->lhs->compile().get_reg());
	Register_Addr_Opd *rhs_result = new Register_Addr_Opd(this->rhs->compile().get_reg());
	Register_Descriptor *rd;
	Register_Addr_Opd *result;
	Compute_IC_Stmt *plus_stmt;
	if(this->lhs->get_data_type() == int_data_type) {
		rd = machine_desc_object.get_new_register<gp_data>();
		result = new Register_Addr_Opd(rd);
		plus_stmt = new Compute_IC_Stmt(add, lhs_result, rhs_result, result);
	}
	else if(this->lhs->get_data_type() == double_data_type) {
		rd = machine_desc_object.get_new_register<float_reg>();
		result = new Register_Addr_Opd(rd);
		plus_stmt = new Compute_IC_Stmt(add_d, lhs_result, rhs_result, result);
	}
	Code_For_Ast *output = new Code_For_Ast();
	output->set_reg(rd);
	output->append_ics(*plus_stmt);
	return *output;
}


Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & Minus_Ast::compile() {
	Register_Addr_Opd *lhs_result = new Register_Addr_Opd(this->lhs->compile().get_reg());
	Register_Addr_Opd *rhs_result = new Register_Addr_Opd(this->rhs->compile().get_reg());
	Register_Descriptor *rd;
	Register_Addr_Opd *result;
	Compute_IC_Stmt *minus_stmt;
	if(this->lhs->get_data_type() == int_data_type) {
		rd = machine_desc_object.get_new_register<gp_data>();
		result = new Register_Addr_Opd(rd);
		minus_stmt = new Compute_IC_Stmt(sub, lhs_result, rhs_result, result);
	}
	else if(this->lhs->get_data_type() == double_data_type) {
		rd = machine_desc_object.get_new_register<float_reg>();
		result = new Register_Addr_Opd(rd);
		minus_stmt = new Compute_IC_Stmt(sub_d, lhs_result, rhs_result, result);
	}
	Code_For_Ast *output = new Code_For_Ast();
	output->set_reg(rd);
	output->append_ics(*minus_stmt);
	return *output;
}


Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & Divide_Ast::compile() {
	Register_Addr_Opd *lhs_result = new Register_Addr_Opd(this->lhs->compile().get_reg());
	Register_Addr_Opd *rhs_result = new Register_Addr_Opd(this->rhs->compile().get_reg());
	Register_Descriptor *rd;
	Register_Addr_Opd *result;
	Compute_IC_Stmt *divide_stmt;
	if(this->lhs->get_data_type() == int_data_type) {
		rd = machine_desc_object.get_new_register<gp_data>();
		result = new Register_Addr_Opd(rd);
		divide_stmt = new Compute_IC_Stmt(divd, lhs_result, rhs_result, result);
	}
	else if(this->lhs->get_data_type() == double_data_type) {
		rd = machine_desc_object.get_new_register<float_reg>();
		result = new Register_Addr_Opd(rd);
		divide_stmt = new Compute_IC_Stmt(div_d, lhs_result, rhs_result, result);
	}
	Code_For_Ast *output = new Code_For_Ast();
	output->set_reg(rd);
	output->append_ics(*divide_stmt);
	return *output;
}

Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & Mult_Ast::compile() {
	Register_Addr_Opd *lhs_result = new Register_Addr_Opd(this->lhs->compile().get_reg());
	Register_Addr_Opd *rhs_result = new Register_Addr_Opd(this->rhs->compile().get_reg());
	Register_Descriptor *rd;
	Register_Addr_Opd *result;
	Compute_IC_Stmt *mult_stmt;
	if(this->lhs->get_data_type() == int_data_type) {
		rd = machine_desc_object.get_new_register<gp_data>();
		result = new Register_Addr_Opd(rd);
		mult_stmt = new Compute_IC_Stmt(mult, lhs_result, rhs_result, result);
	}
	else if(this->lhs->get_data_type() == double_data_type) {
		rd = machine_desc_object.get_new_register<float_reg>();
		result = new Register_Addr_Opd(rd);
		mult_stmt = new Compute_IC_Stmt(mult_d, lhs_result, rhs_result, result);
	}
	Code_For_Ast *output = new Code_For_Ast();
	output->set_reg(rd);
	output->append_ics(*mult_stmt);
	return *output;
}

Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}

Code_For_Ast & UMinus_Ast::compile() {
    Register_Addr_Opd *lhs_result = new Register_Addr_Opd(this->lhs->compile().get_reg());
	Register_Addr_Opd *rhs_result = new Register_Addr_Opd(this->rhs->compile().get_reg());
	Register_Descriptor *rd;
	Register_Addr_Opd *result;
	Compute_IC_Stmt *uminus_stmt;
	if(this->lhs->get_data_type() == int_data_type) {
		rd = machine_desc_object.get_new_register<gp_data>();
		result = new Register_Addr_Opd(rd);
		uminus_stmt = new Compute_IC_Stmt(uminus, lhs_result, rhs_result, result);
	}
	else if(this->lhs->get_data_type() == double_data_type) {
		rd = machine_desc_object.get_new_register<float_reg>();
		result = new Register_Addr_Opd(rd);
		uminus_stmt = new Compute_IC_Stmt(uminus_d, lhs_result, rhs_result, result);
	}
	Code_For_Ast *output = new Code_For_Ast();
	output->set_reg(rd);
	output->append_ics(*uminus_stmt);
	return *output;
}


Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {
  
}

Code_For_Ast & Conditional_Expression_Ast::compile() {
 //    Register_Descriptor * lhs_result = this->lhs.compile().get_reg();
	// Register_Descriptor * rhs_result = this->rhs.compile().get_reg();
 //    Register_Descriptor * cond_result = this->cond.compile().get_reg();

 //    // label1 = new Label_IC_Stmt(this->cond)
 //    Register_Descriptor *result = machine_desc_object.get_new_register(lhs_result->get_use_category());
 //    Compute_IC_Stmt *cond_stmt = lhs_result;
 //    Code_For_Ast *output = new Code_For_Ast();
 //    output->set_reg(result);
 //    output->append_ics(*cond_stmt);

 //    return *output;
}


Code_For_Ast & Return_Ast::compile() {

}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {

}


Code_For_Ast & Relational_Expr_Ast::compile() {

}

Code_For_Ast & Logical_Expr_Ast::compile() {

}

Code_For_Ast & Selection_Statement_Ast::compile() {

}

Code_For_Ast & Iteration_Statement_Ast::compile() {

}

Code_For_Ast & Sequence_Ast::compile() {

}
