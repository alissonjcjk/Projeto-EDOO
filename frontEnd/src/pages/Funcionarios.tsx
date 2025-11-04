import { useState, useEffect } from 'react'
import Modal from '../components/modal/Modal'
import FuncionariosForm from '../components/modal/FuncionarioForm'
import { api } from '../services/api'

interface Funcionario {
  id: number;
  name: string;
  email: string;
  phone: string;
  specialty: string;
  //  Você pode adicionar horário e salário se quiser
  horario: string;
  salario: string;
}

export default function FuncionariosPage() {
  const [open, setOpen] = useState(false)
  const [funcionarios, setFuncionarios] = useState<Funcionario[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  // Carregar funcionários do backend
  useEffect(() => {
    loadFuncionarios();
  }, []);

  const loadFuncionarios = async () => {
    try {
      setLoading(true);
      const data = await api.getBarbers();
      setFuncionarios(data);
    } catch (err) {
      console.error('Erro ao carregar funcionários:', err);
      setError('Erro ao carregar funcionários');
    } finally {
      setLoading(false);
    }
  };

  const handleSave = () => {
    setOpen(false);
    loadFuncionarios(); // Recarregar a lista após salvar
  };

  const handleEditar = (id: number) => {
    console.log('Editar funcionário:', id);
    // Implementar edição
  };

  const handleExcluir = (id: number) => {
    // Aqui você implementará a exclusão no backend
    setFuncionarios(funcionarios.filter(funcionario => funcionario.id !== id));
  };

  if (loading) {
    return <div className="p-6">Carregando funcionários...</div>;
  }

  if (error) {
    return <div className="p-6 text-red-600">{error}</div>;
  }

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
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Especialidade</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Horário</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Salário</th>
                <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">Ações</th>
              </tr>
            </thead>
            <tbody className="bg-white divide-y divide-gray-200">
              {funcionarios.map((funcionario) => (
                <tr key={funcionario.id} className="hover:bg-gray-50 transition-colors">
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm font-medium text-gray-900">{funcionario.name}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.email}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.phone}</div>
                  </td>
                  <td className="px-6 py-4 whitespace-nowrap">
                    <div className="text-sm text-gray-900">{funcionario.specialty}</div>
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
        <FuncionariosForm onCancel={() => setOpen(false)} onSave={handleSave} />
      </Modal>
    </div>
  );
}