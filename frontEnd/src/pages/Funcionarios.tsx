import { useState } from 'react'
import Modal from '../components/modal/Modal'
import FuncionariosForm from '../components/modal/FuncionarioForm'

interface Funcionario {
  id: number;
  nome: string;
  email: string;
  contato: string;
  funcao: string;
  horario: string;
  salario: string;
}

export default function FuncionariosPage() {
  const [open, setOpen] = useState(false)
  const [funcionarios, setFuncionarios] = useState<Funcionario[]>([
    {
      id: 1,
      nome: 'Francisco',
      email: 'frsco@chu.qlc.br',
      contato: '(11) 99999-8888',
      funcao: 'Barbeiro',
      horario: '09:00 - 18:00',
      salario: 'R$ 3300,00'
    },
    {
      id: 2,
      nome: 'Francisco',
      email: 'frsco@chu.qlc.br',
      contato: '(11) 99999-8888',
      funcao: 'Barbeiro',
      horario: '09:00 - 18:00',
      salario: 'R$ 3300,00'
    },
    {
      id: 3,
      nome: 'Francisco',
      email: 'frsco@chu.qlc.br',
      contato: '(11) 99999-8888',
      funcao: 'Barbeiro',
      horario: '09:00 - 18:00',
      salario: 'R$ 3300,00'
    }
  ]);

  const handleEditar = (id: number) => {
    console.log('Editar funcionário:', id);
    // Aqui você integrará com o backend
  };

  const handleExcluir = (id: number) => {
    setFuncionarios(funcionarios.filter(funcionario => funcionario.id !== id));
    // Aqui você integrará com o backend
  };

  return (
    <div className="p-6">
      <div className="mb-8">
        <h1 className="text-3xl font-semibold mb-2">Funcionários</h1>
        <p className="text-xl text-gray-600">Gerencie a equipe da barbearia</p>
      </div>

      <div className="bg-white rounded-lg border border-gray-200 overflow-hidden">
        <div className="overflow-x-auto">
          <table className="min-w-full divide-y divide-gray-200">
            <thead className="bg-gray-50">
              <tr>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Nome</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Email</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Contato</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Função</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Horário</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Salário</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Ações</th>
              </tr>
            </thead>
            <tbody className="bg-white divide-y divide-gray-200">
              {funcionarios.map((funcionario) => (
                <tr key={funcionario.id} className="hover:bg-gray-50 transition-colors">
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm font-medium text-gray-900">{funcionario.nome}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.email}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.contato}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.funcao}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.horario}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.salario}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap text-sm font-medium">
                    <button 
                      onClick={() => handleEditar(funcionario.id)}
                      className="text-blue-600 hover:text-blue-900 mr-4 font-semibold"
                    >
                      Editar
                    </button>
                    <button 
                      onClick={() => handleExcluir(funcionario.id)}
                      className="text-red-600 hover:text-red-900 font-semibold"
                    >
                      Excluir
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>

        <div className="border-t border-gray-200 px-6 py-4 bg-gray-50">
          <button 
            onClick={() => setOpen(true)}
            className="bg-red-600 text-white px-6 py-2 rounded-lg hover:bg-red-700 transition duration-200 font-semibold"
            aria-label="Novo Funcionário"
          >
            + Novo Funcionário
          </button>
        </div>
      </div>

      <Modal isOpen={open} onClose={() => setOpen(false)} title="Novo Funcionário">
			<FuncionariosForm onCancel={() => setOpen(false)} onSave={() => setOpen(false)} />
		</Modal>

			{/* conteúdo da página vai aqui */}
    </div>
  );
}